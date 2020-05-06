//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <array>
#include <memory>
#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/logic/tribool.hpp"
#include "boost/tuple/tuple.hpp"

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

    explicit Connection(boost::asio::io_service& service,
                        ConnectionManager& manager);
    // create socket to connect with server
    // connection manager to manage connections
    // handler to handle requests

    void start();
    boost::asio::ip::tcp::socket& socket() { return this->socket_;}  // get socket associated with connection
    void stop() { socket_.close();}

private:
    boost::asio::ip::tcp::socket socket_;
    ConnectionManager manager_;
    Response response_;
    Handler handler_;
    Request request_;

    std::array<char, 1024> buffer_;  // best variant

    void doRead(const boost::system::error_code& e,
                std::size_t bytes_transferred);  // async read
    void doWrite(const boost::system::error_code& e);  // async write
};

#endif //SERVER_CONNECTION_H
