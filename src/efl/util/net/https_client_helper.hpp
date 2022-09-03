#pragma once

#include <string>

namespace efl::util::net
{
    class https_client_helper
    {
    public:
        static std::string request(const std::string &server, const std::string &path);
    };
} // namespace efl::util::net