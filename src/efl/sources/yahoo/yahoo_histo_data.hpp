#pragma once

#include <map>
#include <string>

#include "efl/date.h"
#include "efl/stock_data.hpp"

namespace efl::sources::yahoo
{
    struct yahoo_ohlcv_t : public ohlcv_t {
        double _adj_close = 0;

        std::string to_string() const;
        
        static std::string csv_header();

        std::string to_csv() const;

        void from_csv(const std::string& line, char separator =  ',');

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