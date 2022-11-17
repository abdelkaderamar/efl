#include "yahoo_provider.hpp"

#include <iostream>
#include <fstream>

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
        : _yahoo_config{config}
    {
    }

    std::vector<yahoo_quote_t> yahoo_provider::quote(const std::string &symbol)
    {
        std::vector<yahoo_quote_t> quotes;
        std::string url = yahoo_helper::get_quote_path(_yahoo_config, symbol);
        std::string result = efl::util::net::https_client_helper::request(_yahoo_config.host(), url);

        spdlog::info("{}", result);

        auto j = json::parse(result);

        auto qr = j["quoteResponse"];

        auto r = qr["result"];
        
        for (json::size_type i = 0; i < r.size(); ++i)
        {
            spdlog::info("***************************************");
            spdlog::info("{}", r.at(i));

            yahoo_quote_t q;
            q.from_json(r.at(i));
            quotes.push_back(q);

            spdlog::info("Long name = {}", q.longName);
        }

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
        
        std::stringstream ss;
        ss << result;
        std::string line;
        std::getline(ss, line, '\n'); // header
        while (std::getline(ss, line, '\n')) {
            auto ohlcv = yahoo_helper::parse_histo_data(line);
            histo_data._data[ohlcv._date] = ohlcv;
        }
        return histo_data;
    }
}