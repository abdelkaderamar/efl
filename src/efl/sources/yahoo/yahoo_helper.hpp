#pragma once

#include <string>

#include "yahoo_config.hpp"
#include "yahoo_histo_data.hpp"
#include "efl/date.h"

namespace efl::sources::yahoo
{
    class yahoo_helper
    {
    public:
        static std::string get_quote_path(yahoo_config &config, const std::string &symbol);
        
        static std::string get_download_path(yahoo_config &config, const std::string &symbol);

        static date::year_month_day parse_date(const std::string &str);

        static yahoo_ohlcv_t parse_histo_data(const std::string &str);

        static time_t get_epoch(const date::year_month_day& d);

        static std::string get_histo_request(const std::string &symbol, const date::year_month_day &start,
                                           const date::year_month_day &end);
    };
}