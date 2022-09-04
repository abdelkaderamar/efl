#include "yahoo_helper.hpp"

namespace efl::sources::yahoo
{
    std::string yahoo_helper::get_quote_path(yahoo_config &config, const std::string &symbol)
    {
        return config.query_url() + config.quote_api() + "?symbols=" + symbol;
    }

    std::string yahoo_helper::get_download_path(yahoo_config &config, const std::string &symbol)
    {
        return config.query_url() + config.download_api() + '/' + symbol;
    }

}