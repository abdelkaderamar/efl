#pragma once

#include <chrono>
#include <vector>

#include "yahoo_config.hpp"
#include "yahoo_quote.hpp"
#include "yahoo_histo_data.hpp"

namespace efl::sources::yahoo
{
    class yahoo_provider
    {
    public:
        yahoo_provider(const yahoo_config config = yahoo_config::_default);

        std::vector<yahoo_quote_t> quote(const std::string &symbol);

        yahoo_histo_data_t histo(const std::string &symbol, const date::year_month_day &start,
                                 const date::year_month_day &end);

    private:
        yahoo_config _yahoo_config;

        std::chrono::time_point<std::chrono::system_clock> _last_request_time;

        void check_delay();
        void set_request_time(); 
    };
}