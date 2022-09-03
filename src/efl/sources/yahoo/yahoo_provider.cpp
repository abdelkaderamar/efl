#include "yahoo_provider.hpp"

#include <iostream>

#include <nlohmann/json.hpp>

#include "efl/util/net/https_client_helper.hpp"
#include "yahoo_helper.hpp"
#include "yahoo_quote.hpp"

namespace efl::sources::yahoo
{
    using json = nlohmann::json;

    yahoo_provider::yahoo_provider(const yahoo_config config /* = yahoo_config::_default */)
        : _yahoo_config{config}
    {
    }

    void yahoo_provider::quote(const std::string &symbol)
    {
        std::string url = yahoo_helper::get_quote_path(_yahoo_config, symbol);
        std::string result = efl::util::net::https_client_helper::request(_yahoo_config.host(), url);

        std::cout << result << std::endl;

        auto j = json::parse(result);

        auto qr = j["quoteResponse"];

        auto r = qr["result"];

        for (json::size_type i = 0; i < r.size(); ++i)
        {
            std::cout << "***************************************" << std::endl;
            std::cout << std::setw(4) << r.at(i) << std::endl;

            yahoo_quote_t q;
            q.from_json(r.at(i));

            std::cout << "Long name = " << q.longName << std::endl;
        }
    }
}