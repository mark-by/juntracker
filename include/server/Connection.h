//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <iostream>

#include "Response.h"
#include "Request.h"
#include "ConnectionManager.h"
#include "Handler.h"

class ConnectionManager;

class Connection: public std::enable_shared_from_this<Connection> {
public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    // decline "="

    explicit Connection(boost::asio::ip::tcp::socket socket,
                        ConnectionManager& manager, Handler& handler);
    // create socket to connect with server
    // connection manager toi manage connections
    // handler to handle requests

    void start() { doRead();}
    void stop() { socket_.close();}

private:
    boost::asio::ip::tcp::socket socket_;
    ConnectionManager manager_;
    Response response_;
    Handler handler_;
    Request request_;

    std::array<char, 1024> buffer;

    void doRead();  // async read
    void doWrite();  // async write
};

#endif //SERVER_CONNECTION_H
