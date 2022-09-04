#pragma once

#include "yahoo_config.hpp"

namespace efl::sources::yahoo
{
    class yahoo_provider
    {
    public:
        yahoo_provider(const yahoo_config config = yahoo_config::_default);

        void quote(const std::string &symbol);

        void histo(const std::string &symbol);

    private:
        yahoo_config _yahoo_config;
    };
}