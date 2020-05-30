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

    explicit Connection(boost::asio::io_service& service, ConnectionManager& manager);

    void start();
    void stop() { socket_.close();}

    boost::asio::ip::tcp::socket& socket() { return this->socket_;}  // get socket associated with connection

private:
    boost::asio::ip::tcp::socket socket_;
    ConnectionManager& manager_;
    Handler handler_;

    std::array<char, 1024> buffer_;

    void doRead(const boost::system::error_code& e, std::size_t bytes_transferred);  // handle requests
    void doWrite(const boost::system::error_code& e);  // send response to client
};

#endif  // SERVER_CONNECTION_H
