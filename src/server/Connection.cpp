//
// Created by gg on 15.04.2020.
//

#include "Connection.h"

Connection::Connection(boost::asio::ip::tcp::socket socket,
        ConnectionManager& manager, Handler& handler): socket_(std::move(socket)), handler_(handler) {
    this->manager_ = manager;
};

void Connection::doRead() {
    auto self(shared_from_this());  // keep connect alive in lambda-function
    /*socket_.async_read_some(
            boost::asio::buffer(buffer),

            );*/
}
