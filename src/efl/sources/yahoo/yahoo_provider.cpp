#include "yahoo_provider.hpp"

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

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

        std::cout << result << std::endl;

        auto j = json::parse(result);

        auto qr = j["quoteResponse"];

        auto r = qr["result"];

        for (json::size_type i = 0; i < r.size(); ++i)
        {
            std::cout << "***************************************" << std::endl;
            std::cout << std::setw(4) << r.at(i) << std::endl;

            yahoo_quote_t q;
            q.from_json(r.at(i));
            quotes.push_back(q);

            std::cout << "Long name = " << q.longName << std::endl;
        }

        return quotes;
    }

    //TODO: convert to structured data
    /*
    2022-03-01,19.000000,19.430000,17.830000,18.320000,18.320000,44003000
    The format is 
7    Date	Open	High	Low	Close	Adj Close	Volume
    
    */
    yahoo_histo_data_t yahoo_provider::histo(const std::string &symbol)
    {
        // download/AMC?period1=1387324800&period2=1652140800&interval=1d&events=history&includeAdjustedClose=true
        yahoo_histo_data_t histo_data{symbol};

        std::string url = yahoo_helper::get_download_path(_yahoo_config, symbol) +
                          "?period1=1387324800&period2=1652140800&interval=1d&events=history&includeAdjustedClose=true";
        std::string result = efl::util::net::https_client_helper::request(_yahoo_config.host(), url);
        
        // std::ofstream data_file{"histo_data.csv"};
        // data_file << result;
        // data_file.close();

        // io::CSVReader<7,
        //           io::trim_chars<' ', '\t'> ,
        //           io::double_quote_escape<',', '"'>
        //           > csv_reader{"histo_data.csv"};
        // // skip the header
        // csv_reader.read_header(io::ignore_no_column,
        //                    "Date","Open","High","Low","Close","Adj Close", "Volume");
        // std::string date_str, open_str, high_str, low_str, close_str, adj_close_str, volume_str;
        // while (csv_reader.read_row(date_str, open_str, high_str, low_str, close_str, adj_close_str, volume_str)) {
        //     yahoo_ohlcv_t ohlcv;
        //     std::cout << date_str << std::endl;
        //     ohlcv._date = yahoo_helper::parse_date(date_str);
        //     ohlcv._open = std::stod(open_str);
        //     ohlcv._close = std::stod(close_str);
        //     std::cout << ohlcv._date << ": \t" << ohlcv._open << std::endl;
        // }
        std::stringstream ss;
        ss << result;
        std::string line;
        std::getline(ss, line, '\n'); // header
        while (std::getline(ss, line, '\n')) {
            // std::cout << line << std::endl;
            auto ohlcv = yahoo_helper::parse_histo_data(line);
            histo_data._data[ohlcv._date] = ohlcv;
        }
        return histo_data;
    }
}