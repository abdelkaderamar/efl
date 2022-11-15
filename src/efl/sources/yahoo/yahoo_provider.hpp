#pragma once

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

        yahoo_histo_data_t histo(const std::string &symbol);

    private:
        yahoo_config _yahoo_config;
    };
}