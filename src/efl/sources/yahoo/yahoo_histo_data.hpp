#pragma once

#include <map>
#include <string>

#include "efl/date.h"

namespace efl::sources::yahoo
{
    struct yahoo_ohlcv_t {
        date::year_month_day _date;
        double _open = 0;
        double _high = 0;
        double _low = 0;
        double _close = 0;
        double _adj_close = 0;
        double _volume = 0;

        std::string to_string() const;

        bool is_valid() const;
    };

    struct yahoo_histo_data_t {
        yahoo_histo_data_t(const std::string& symbol): _symbol{symbol} 
        {}

        std::string _symbol;
        std::map<date::year_month_day, yahoo_ohlcv_t> _data;
    };

    std::ostream& operator<<(std::ostream& os, const yahoo_ohlcv_t& ohlcv);
}