//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <array>
#include <iostream>
#include <memory>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/logic/tribool.hpp"

#include "Handler.h"

class ConnectionManager;

class Connection: public std::enable_shared_from_this<Connection> {
public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    // decline "="

    explicit Connection(boost::asio::io_service& service, ConnectionManager& manager);
    // create socket to connect with server
    // connection manager to manage connections
    // handler to handle requests

    void start();
    boost::asio::ip::tcp::socket& socket() { return this->socket_;}  // get socket associated with connection
    void stop() { socket_.close();}

private:
    boost::asio::ip::tcp::socket socket_;
    ConnectionManager& manager_;
    Handler handler_;

    std::array<char, 1024> buffer_;  // best variant; std::vector not thread-safety

    void doRead(const boost::system::error_code& e,
                std::size_t bytes_transferred);  // async read from socket and handle request
    void doWrite(const boost::system::error_code& e);  // async write to socket and send to client callback
};

#endif  // SERVER_CONNECTION_H
