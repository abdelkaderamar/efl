#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

namespace efl::util::net
{
    class https_client
    {
    public:
        https_client(boost::asio::io_service& io_service,
           boost::asio::ssl::context& context);

        void request(const std::string& server, const std::string& path);
    
        std::string response_content();

    protected:
        void handle_resolve(const boost::system::error_code &err,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

        bool verify_certificate(bool preverified,
                                boost::asio::ssl::verify_context &ctx);

        void handle_connect(const boost::system::error_code &err);

        void handle_handshake(const boost::system::error_code& error);

        void handle_write_request(const boost::system::error_code& err);

        void handle_read_status_line(const boost::system::error_code& err);

        void handle_read_headers(const boost::system::error_code& err);

        void handle_read_content(const boost::system::error_code &err);

    private:
        boost::asio::ip::tcp::resolver _resolver;
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;
        boost::asio::streambuf _request;
        boost::asio::streambuf _response;
    };

}