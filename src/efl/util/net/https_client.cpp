#include "https_client.hpp"

#include <iostream>

namespace efl::util::net
{
    https_client::https_client(boost::asio::io_service &io_service,
                               boost::asio::ssl::context &context)
        : _resolver(io_service),
          _socket(io_service, context)
    {
    }

    void https_client::request(const std::string &server, const std::string &path)
    {
        std::ostream request_stream(&_request);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        boost::asio::ip::tcp::resolver::query query(server, "https");
        _resolver.async_resolve(query,
                                boost::bind(&https_client::handle_resolve, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::iterator));
    }

    void https_client::handle_resolve(const boost::system::error_code &err,
                                      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    {
        if (!err)
        {
            std::cout << "Resolve OK" << std::endl;
            _socket.set_verify_mode(boost::asio::ssl::verify_peer);
            _socket.set_verify_callback(
                boost::bind(&https_client::verify_certificate, this, _1, _2));

            boost::asio::async_connect(_socket.lowest_layer(), endpoint_iterator,
                                       boost::bind(&https_client::handle_connect, this,
                                                   boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error resolve: " << err.message() << std::endl;
        }
    }

    bool https_client::verify_certificate(bool preverified,
                                          boost::asio::ssl::verify_context &ctx)
    {
        // The verify callback can be used to check whether the certificate that is
        // being presented is valid for the peer. For example, RFC 2818 describes
        // the steps involved in doing this for HTTPS. Consult the OpenSSL
        // documentation for more details. Note that the callback is called once
        // for each certificate in the certificate chain, starting from the root
        // certificate authority.

        // In this example we will simply print the certificate's subject name.
        char subject_name[256];
        X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        std::cout << "Verifying " << subject_name << std::endl;

        return preverified;
    }

    void https_client::handle_connect(const boost::system::error_code &err)
    {
        if (!err)
        {
            std::cout << "Connect OK " << std::endl;
            _socket.async_handshake(boost::asio::ssl::stream_base::client,
                                    boost::bind(&https_client::handle_handshake, this,
                                                boost::asio::placeholders::error));
        }
        else
        {
            std::cerr << "Connect failed: " << err.message() << std::endl;
        }
    }

    void https_client::handle_handshake(const boost::system::error_code &error)
    {
        if (!error)
        {
            std::cout << "Handshake OK " << std::endl;
            std::cout << "Request: " << std::endl;
            const char *header = boost::asio::buffer_cast<const char *>(_request.data());
            std::cout << header << std::endl;

            // The handshake was successful. Send the request.
            boost::asio::async_write(_socket, _request,
                                     boost::bind(&https_client::handle_write_request, this,
                                                 boost::asio::placeholders::error));
        }
        else
        {
            std::cerr << "Handshake failed: " << error.message() << std::endl;
        }
    }

    void https_client::handle_write_request(const boost::system::error_code &err)
    {
        if (!err)
        {
            // Read the response status line. The response_ streambuf will
            // automatically grow to accommodate the entire line. The growth may be
            // limited by passing a maximum size to the streambuf constructor.
            boost::asio::async_read_until(_socket, _response, "\r\n",
                                          boost::bind(&https_client::handle_read_status_line, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cerr << "Error write req: " << err.message() << std::endl;
        }
    }

    void https_client::handle_read_status_line(const boost::system::error_code &err)
    {
        if (!err)
        {
            // Check that response is OK.
            std::istream response_stream(&_response);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);
            if (!response_stream || http_version.substr(0, 5) != "HTTP/")
            {
                std::cout << "Invalid response\n";
                return;
            }
            if (status_code != 200)
            {
                std::cout << "Response returned with status code ";
                std::cout << status_code << "\n";
                return;
            }
            std::cout << "Status code: " << status_code << "\n";

            // Read the response headers, which are terminated by a blank line.
            boost::asio::async_read_until(_socket, _response, "\r\n\r\n",
                                          boost::bind(&https_client::handle_read_headers, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cerr << "Error: " << err.message() << std::endl;
        }
    }

    void https_client::handle_read_headers(const boost::system::error_code &err)
    {
        if (!err)
        {
            // Process the response headers.
            std::istream response_stream(&_response);
            std::string header;
            while (std::getline(response_stream, header) && header != "\r")
                std::cout << header << "\n";
            std::cout << "\n";

            // Write whatever content we already have to output.
            if (_response.size() > 0)
                std::cout << &_response;

            // Start reading remaining data until EOF.
            boost::asio::async_read(_socket, _response,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&https_client::handle_read_content, this,
                                                boost::asio::placeholders::error));
        }
        else
        {
            std::cerr << "Error: " << err << std::endl;
        }
    }

    void https_client::handle_read_content(const boost::system::error_code &err)
    {
        if (!err)
        {
            // Continue reading remaining data until EOF.
            boost::asio::async_read(_socket, _response,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&https_client::handle_read_content, this,
                                                boost::asio::placeholders::error));
        }
        else if (err != boost::asio::error::eof)
        {
            std::cerr << "Error: " << err << std::endl;
        }
    }

    std::string https_client::response_content()
    {
        boost::asio::streambuf::const_buffers_type bufs = _response.data();
        std::string str(boost::asio::buffers_begin(bufs),
                        boost::asio::buffers_begin(bufs) + bufs.size());
        return str;
    }
}