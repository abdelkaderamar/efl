#pragma once

#include <map>
#include <string>

#include "efl/date.h"

namespace efl::sources::yahoo
{
    struct yahoo_ohlcv_t {
        date::year_month_day _date;
        double _open;
        double _high;
        double _low;
        double _close;
        double _adj_close;
        double _volume;

        std::string to_string() const;
    };

    struct yahoo_histo_data_t {
        yahoo_histo_data_t(const std::string& symbol): _symbol{symbol} 
        {}

        std::string _symbol;
        std::map<date::year_month_day, yahoo_ohlcv_t> _data;
    };

    std::ostream& operator<<(std::ostream& os, const yahoo_ohlcv_t& ohlcv);
}