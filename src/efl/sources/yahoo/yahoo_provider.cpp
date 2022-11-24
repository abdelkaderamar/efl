#include "yahoo_provider.hpp"

#include <fstream>
#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "efl/csv.h"
#include "efl/util/net/https_client_helper.hpp"
#include "efl/csv_parser.hpp"
#include "yahoo_helper.hpp"
#include "yahoo_quote.hpp"

namespace efl::sources::yahoo
{
    using json = nlohmann::json;

    yahoo_provider::yahoo_provider(const yahoo_config config /* = yahoo_config::_default */)
        : _yahoo_config{config},
        _last_request_time(std::chrono::time_point<std::chrono::system_clock>::min())
    {
    }

    std::vector<yahoo_quote_t> yahoo_provider::quote(const std::string &symbol)
    {
        check_delay();

        std::vector<yahoo_quote_t> quotes;
        std::string url = yahoo_helper::get_quote_path(_yahoo_config, symbol);
        spdlog::info("Requesting yahoo finance with the following request {}", url);
        std::string result = efl::util::net::https_client_helper::request(_yahoo_config.host(), url);

        spdlog::info("HTTP result = [{}]", result);

        auto j = json::parse(result);

        auto qr = j["quoteResponse"];

        auto r = qr["result"];
        
        for (json::size_type i = 0; i < r.size(); ++i)
        {
            spdlog::info("***************************************");
            spdlog::info("r.at({}) = [{}]", i, r.at(i).dump());
            spdlog::info("***************************************");

            yahoo_quote_t q;
            q.from_json(r.at(i));
            quotes.push_back(q);

            spdlog::info("Long name = {}", q.longName);
        }

        set_request_time();

        return quotes;
    }

    //TODO: convert to structured data
    /*
    2022-03-01,19.000000,19.430000,17.830000,18.320000,18.320000,44003000
    The format is 
7    Date	Open	High	Low	Close	Adj Close	Volume
    
    */
    yahoo_histo_data_t yahoo_provider::histo(const std::string &symbol,
        const date::year_month_day& start,
        const date::year_month_day& end
        )
    {
        check_delay();
        // download/AMC?period1=1387324800&period2=1652140800&interval=1d&events=history&includeAdjustedClose=true
        // period1=1387324800
        // period2=1652140800
        // interval=1d
        // events=history

        std::string request_url = yahoo_helper::get_histo_request(symbol, start, end);

        yahoo_histo_data_t histo_data{symbol};

        std::string url = yahoo_helper::get_download_path(_yahoo_config, symbol) + request_url;
                          // "?period1=1387324800&period2=1652140800&interval=1d&events=history&includeAdjustedClose=true";
        std::string result = efl::util::net::https_client_helper::request(_yahoo_config.host(), url);
        
        spdlog::info("Result = [{}]", result);

        std::stringstream ss;
        ss << result;
        std::string line;
        std::getline(ss, line, '\n'); // header
        while (std::getline(ss, line, '\n')) {
            auto ohlcv = yahoo_helper::parse_histo_data(line);
            if (ohlcv.is_valid()) {
                histo_data._data[ohlcv._date] = ohlcv;
            }
            else {
                spdlog::info("Ignoring {}", line);
            }
        }

        set_request_time();

        return histo_data;
    }

    void yahoo_provider::check_delay() {
        if (_last_request_time == std::chrono::time_point<std::chrono::system_clock>::min()) {
            _last_request_time = std::chrono::system_clock::now();
            return;
        }
        const std::chrono::time_point<std::chrono::system_clock> now =
            std::chrono::system_clock::now();
        const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - _last_request_time).count();
        std::chrono::milliseconds waiting_time{1000-diff}; // TODO make it configurable
        std::cout << "Waiting for " << waiting_time.count() << " ms" << std::endl;
        std::this_thread::sleep_for(waiting_time);
    }

    void yahoo_provider::set_request_time() {
        _last_request_time = std::chrono::system_clock::now();
    }
}