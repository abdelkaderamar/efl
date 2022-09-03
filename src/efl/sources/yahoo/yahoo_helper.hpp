#pragma once

#include <string>

#include "yahoo_config.hpp"

namespace efl::sources::yahoo
{
    class yahoo_helper
    {
    public:
        static std::string get_quote_path(yahoo_config &config, const std::string &symbol);
    };
}