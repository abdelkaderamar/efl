#include "https_client_helper.hpp"

#include <iostream>

#include <spdlog/spdlog.h>

#include "https_client.hpp"



namespace efl::util::net
{
    std::string https_client_helper::request(const std::string &server, const std::string &path)
    {
        try
        {
            boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
            ctx.set_default_verify_paths();

            boost::asio::io_service io_service;

            https_client client{io_service, ctx};
            client.request(server, path);
            
            io_service.run();

            return client.response_content();
        }
        catch (std::exception &e)
        {
            spdlog::error("Exception {}", e.what());
            return "";
        }
        catch (...)
        {
            spdlog::error("Exception");
            return "";
        }
    }
}