#include "yahoo_helper.hpp"

#include <regex>

namespace efl::sources::yahoo
{
    std::string yahoo_helper::get_quote_path(yahoo_config &config, const std::string &symbol)
    {
        return config.query_url() + config.quote_api() + "?symbols=" + symbol;
    }

    std::string yahoo_helper::get_download_path(yahoo_config &config, const std::string &symbol)
    {
        return config.query_url() + config.download_api() + '/' + symbol;
    }

    date::year_month_day yahoo_helper::parse_date(const std::string &str)
    {
        static std::regex re("([0-9]{4})-([0-1][0-9])-([0-3][0-9])");
        std::smatch m;
        if (std::regex_match(str, m, re))
        {
            if (m.size() == 4)
            {
                //      std::cout << m[1] << std::endl;
                auto day = date::day{(unsigned)std::stoi(m[3])};
                //      std::cout << m[2] << std::endl;
                auto month = date::month{(unsigned)std::stoi(m[2])};
                //      std::cout << m[3] << std::endl;
                auto year = date::year{std::stoi(m[1])};

                return date::year_month_day{year, month, day};
            }
        }

        return date::year_month_day{};
    }

    yahoo_ohlcv_t yahoo_helper::parse_histo_data(const std::string &str) {
        yahoo_ohlcv_t ohlcv;
        std::string date_str, open_str, high_str, low_str, close_str, adj_close_str, volume_str;
        
        std::stringstream is;
        std::string token;
        auto parse_double_value = [&is, &token]() {
            std::getline(is, token, ',');
            return std::stod(token);
        };
        is << str;
        std::getline(is, date_str, ',');
        ohlcv._date = parse_date(date_str);
        ohlcv._open = parse_double_value();
        ohlcv._low = parse_double_value();
        ohlcv._high = parse_double_value();
        ohlcv._close = parse_double_value();
        ohlcv._adj_close = parse_double_value();
        ohlcv._volume = parse_double_value();
        return ohlcv;
    }

}