//
// Created by gg on 15.04.2020.
//

#include "Connection.h"

Connection::Connection(boost::asio::ip::tcp::socket socket,
        ConnectionManager& manager, Handler& handler):
        socket_(std::move(socket)), handler_(handler), buffer_() {
    this->manager_ = manager;
};

void Connection::start() {
    socket_.async_read_some(
            boost::asio::buffer(buffer_),
            boost::bind(&Connection::doRead, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
            );
}

void Connection::doRead(const boost::system::error_code& error,
                        std::size_t bytes_transferred) {
    if (!error) {
        boost::logic::tribool result;  // need to check all received data from client
        // boost::tie(result, boost::tuples::ignore) =;

        if (result) {
            // big switch to choose api for request
            switch (request_.getWish()) {
                case wishes::schedule:  // enum wishes {}
                    ;  // call handler
            }
            // need to write to response_.buffer or something like this
            boost::asio::async_write(socket_, response_.setBody(buffer_.data()),
                    boost::bind(&Connection::doWrite, shared_from_this(),
                            boost::asio::placeholders::error));  // think this will not work
        } else if (!result) {
            // error
            // handle error
        } else {
            socket_.async_read_some(
                    boost::asio::buffer(buffer_),
                    boost::bind(&Connection::doRead, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred)
            );
        }
    } else if (error != boost::asio::error::operation_aborted) {
        manager_.stop(shared_from_this());
    }
}

void Connection::doWrite(const boost::system::error_code &e) {
    if (!e) {
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }
    if (e != boost::asio::error::operation_aborted) {
        manager_.stop(shared_from_this());
    }
}
