//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "Response.h"
#include "Handler.h"
#include "RequestParser.h"

class ConnectionManager;

class Connection: public std::enable_shared_from_this<this> {
public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    // decline "="

    explicit Connection(boost::asio::ip::tcp::socket socket,
                        ConnectionManager& manager, Handler& handler);
    // create socket to connect with server
    // connection manager toi manage connections
    // handler to handle requests

private:
    // ConnectionManager manager_;
    // Response callback_;
    // RequestParser parser_;
    // Handler handler_;
    // Request request_;
    std::array<char, 1024> buffer;

    void doRead();  // async read
    void doWrite();  // async write
    boost::asio::ip::tcp::socket socket_;
};

#endif //SERVER_CONNECTION_H
