#pragma once

#include <string>

namespace efl::sources::yahoo
{
    class yahoo_default_config
    {
    public:
        const static std::string YAHOO_HOST;
        const static std::string QUERY_URL;
        const static std::string QUOTE_API;
    };

    class yahoo_config
    {
    public:
        yahoo_config(const std::string &host, const std::string &query_url,
                     const std::string &quote_api = yahoo_default_config::QUOTE_API)
            : _host{host}, _query_url{query_url}, _quote_api{quote_api}
        {
        }

        const std::string &host() const { return _host; }
        void set_host(const std::string &host) { _host = host; }

        const std::string &query_url() const { return _query_url; }
        void set_query_url(const std::string &query_url) { _query_url = query_url; }

        const std::string &quote_api() const { return _quote_api; }
        void set_quote_api(const std::string &quote_api) { _quote_api = quote_api; }

        static const yahoo_config _default;

    private:
        std::string _host;
        std::string _query_url;
        std::string _quote_api;
    };
}