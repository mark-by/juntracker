//
// Created by gg on 14.04.2020.
//


#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>

/*using namespace boost::asio;
io_service service;

void func(int i) {
    std::cout << "func called, i= " << i << std::endl;
}

void run_dispatch_and_post() {
    for ( int i = 0; i < 10; i += 2) {
        service.dispatch(boost::bind(func, i));
        service.post(boost::bind(func, i + 1));
    }
}

int main(int argc, char* argv[]) {
    service.post(run_dispatch_and_post);
    service.run();
}*/

#include <boost/bind.hpp>
#include "include/server/Server.h"
#include "include/server/Client.h"

/*void test() {
    std::cout << "\ntest\n" << std::endl;

    boost::asio::io_context context_;
    boost::asio::ip::tcp::resolver resolver{context_};

    auto query = boost::asio::ip::tcp::resolver::query{"google.com", "80"};

    resolver.async_resolve(query,
            [](const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iter) {
                for (iter; iter != boost::asio::ip::tcp::resolver::iterator{}; ++iter) {
                    boost::asio::ip::tcp::endpoint endpoint = *iter;
                    std::cout << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
                }
    });

    context_.run();
}*/

class client {
public:
    client(boost::asio::io_context& context, const std::string& server,
           const std::string& path): resolver_(context), sock_(context) {
        std::ostream request_stream(&request_);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        resolver_.async_resolve(server, "http",
                boost::bind(&client::handleResolve, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::results));
    };

private:
    void handleResolve(const boost::system::error_code& err,
                       const boost::asio::ip::tcp::resolver::results_type& endpoints) {
        if (err) {
            std::cout << "Error: " << err.message() << std::endl;
        }

        boost::asio::async_connect(sock_, endpoints,
                boost::bind(&client::handleConnect, this,
                        boost::asio::placeholders::error));
    }

    void handleConnect(const boost::system::error_code& err) {
        if (err) {
            std::cout << "Error: " << err.message() << std::endl;
        }

        boost::asio::async_write(sock_, request_,
                boost::bind(&client::handleWriteRequest, this,
                        boost::asio::placeholders::error));
    }

    void handleWriteRequest(const boost::system::error_code& err) {
        if (err) {
            std::cout << "Error: " << err.message() << std::endl;
        }

        boost::asio::async_read_until(sock_, response_, "\r\n",
                boost::bind(&client::handleReadStatusLine, this,
                        boost::asio::placeholders::error));
    }

    void handleReadStatusLine(const boost::system::error_code& err) {
        if (err) {
            std::cout << "Error: " << err.message() << std::endl;
        }

        std::istream response_stream(&response_);
        std::string http;
        response_stream >> http;

        std::size_t status_code;
        response_stream >> status_code;

        std::string status_msg;
        std::getline(response_stream, status_msg);

        if (!response_stream || http.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            return;
        }

        if (status_code != 200) {
            std::cout << "response returned with code:"
                      << status_code << std::endl;
            return;
        }

        boost::asio::async_read_until(sock_, response_, "\r\n\r\n",
                boost::bind(&client::handleReadHeaders, this,
                        boost::asio::placeholders::error));

    }

    void handleReadHeaders(boost::system::error_code& err) {
        if (err) {
            std::cout << "Error: " << err.message() << std::endl;
        }

        std::istream response_stream(&response_);
        std::string header;

        while (std::getline(response_stream, header) && header != "\r") {
            std::cout << header << std::endl;
        }
        std::cout << std::endl;

        if (response_.size() > 0) {
            std::cout << &response_;
        }

        boost::asio::async_read(sock_, response_,
                boost::asio::transfer_at_least(1),
                boost::bind(&client::handleReadContent, this,
                        boost::asio::placeholders::error));
    }

    void handleReadContent(const boost::system::error_code& err) {
        if (!err) {
            std::cout << &response_;
            boost::asio::async_read(sock_, response_,
                    boost::asio::transfer_at_least(1),
                    boost::bind(&client::handleReadContent, this,
                            boost::asio::placeholders::error));
        } else if (err == boost::asio::error::eof) {
            std::cout << "Error:" << err << std::endl;
        }
    }

    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket sock_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;
};

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            std::cout << "domain path ---- boost.org /LICENSE_1_0.txt\n" << std::endl;
            return 1;
        }

        boost::asio::io_context context_;
        client client(context_, argv[1], argv[2]);
        context_.run();
    } catch (std::exception& exception) {
        std::cout << "Exception: " << exception.what() << std::endl;
    }
    return 0;
}
