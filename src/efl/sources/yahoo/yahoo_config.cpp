#include "yahoo_config.hpp"

namespace efl::sources::yahoo
{
    const std::string yahoo_default_config::YAHOO_HOST = "query1.finance.yahoo.com";
    const std::string yahoo_default_config::QUERY_URL = "/v7/finance/";
    const std::string yahoo_default_config::QUOTE_API = "quote";

    const yahoo_config yahoo_config::_default = yahoo_config{yahoo_default_config::YAHOO_HOST,
                                                             yahoo_default_config::QUERY_URL,
                                                             yahoo_default_config::QUOTE_API};

}