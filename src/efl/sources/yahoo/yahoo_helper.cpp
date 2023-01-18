#include "yahoo_helper.hpp"

#include <ctime>
#include <fstream>
#include <regex>

#include <spdlog/spdlog.h>

#include "efl/util/fmt_util.hpp"

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
                auto day = date::day{(unsigned)std::stoi(m[3])};
                auto month = date::month{(unsigned)std::stoi(m[2])};
                auto year = date::year{std::stoi(m[1])};

                return date::year_month_day{year, month, day};
            }
        }
        spdlog::warn("Cannot parse this date {}", str);
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
        try {
            is << str;
            std::getline(is, date_str, ',');
            ohlcv._date = parse_date(date_str);
            ohlcv._open = parse_double_value();
            ohlcv._low = parse_double_value();
            ohlcv._high = parse_double_value();
            ohlcv._close = parse_double_value();
            ohlcv._adj_close = parse_double_value();
            ohlcv._volume = parse_double_value();
        }
        catch (std::exception& e) {
            spdlog::error("Parsing error of {}. Exception: {}", str, e.what());
        }
        catch (...) {
            spdlog::error("Parsing error of {}", str);
        }
        return ohlcv;
    }

    time_t yahoo_helper::get_epoch(const date::year_month_day& d) 
    {
        struct tm t = {.tm_mday = (int)(static_cast<unsigned>(d.day())),
                        .tm_mon = (int)(static_cast<unsigned>(d.month()) - 1),
                        .tm_year = int(d.year()) - 1900};
        // return std::mktime(&t);
        return timegm(&t);
    }

    std::string yahoo_helper::get_histo_request(const std::string &symbol, const date::year_month_day &start,
                                           const date::year_month_day &end) 
    {
        return "?period1=" + std::to_string(get_epoch(start)) + 
               "&period2=" + std::to_string(get_epoch(end)) + 
               "&interval=1d&events=history&includeAdjustedClose=true";
    }

    yahoo_histo_data_t yahoo_helper::parse_histo_csv_file(const std::string& symbol, const std::string& filename)
    {
        yahoo_histo_data_t histo_data{symbol};
        std::ifstream csv_file(filename, std::ifstream::in);
        if (csv_file.is_open())
        {
            std::string line;
            // Skip the header
            std::getline(csv_file, line);
            while (std::getline(csv_file, line)) {
                yahoo_ohlcv_t ohlcv;
                ohlcv.from_csv(line);
                histo_data._data[ohlcv._date] = ohlcv;
                spdlog::info("data size {}", histo_data._data.size());
                spdlog::info("{}", ohlcv._date);
            }
            csv_file.close();
        }
        else spdlog::error("File [{}] cannot be opened", filename);

        return histo_data;
    }
}