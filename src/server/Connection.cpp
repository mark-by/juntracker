//
// Created by gg on 15.04.2020.
//

#include "Connection.h"

namespace async = boost::asio;
namespace net = boost::asio::ip;

enum rights {
    admin = 0,
    teacher = 1,
    customer = 2
};

Connection::Connection(boost::asio::io_service& service, ConnectionManager& manager, Handler& handler):
    socket_(service), handler_(handler), buffer_() {
    this->manager_ = manager;
};

void Connection::start() {
    socket_.async_read_some(
            boost::asio::buffer(buffer_),
            boost::bind(&Connection::doRead, shared_from_this(),
                    async::placeholders::error,
                    async::placeholders::bytes_transferred)
            );
}

void Connection::doRead(const boost::system::error_code& error,
                        std::size_t bytes_transferred) {
    if (!error) {
        boost::logic::tribool result;  // need to check all received data from client
        // boost::tie(result, boost::tuples::ignore) =;

        // need to read about property_tree

        if (result) {  // true; we read all data
            // big switch to choose api for request
            if (request_.getMethod() == "POST") {
                // handler
                if (request_.getRights() == rights::admin) {
                    // do handle
                } else {
                    // error
                }
            }

            if (request_.getMethod() == "GET") {
                // handler
                switch (request_.getRights()) {
                    case rights::admin:
                        handler_.admin();
                        break;
                    case rights::teacher:
                        handler_.teacher();
                        break;
                    case rights::customer:
                        handler_.customer();
                        break;
                    default:
                        // error
                        break;
                }
            }
            // need to write to response_.buffer or something like this
            async::async_write(socket_,
                    async::buffer(
                            response_.toString().data(),
                            response_.toString().size()
                            ),
                    boost::bind(&Connection::doWrite, shared_from_this(),
                            async::placeholders::error));
        } else {
            socket_.async_read_some(
                    async::buffer(buffer_),
                    boost::bind(&Connection::doRead, shared_from_this(),
                            async::placeholders::error,
                            async::placeholders::bytes_transferred)
            );
        }
    } else if (error != async::error::operation_aborted) {
        manager_.stop(shared_from_this());
    }
}

void Connection::doWrite(const boost::system::error_code &e) {
    if (!e) {
        boost::system::error_code ignored_ec;
        socket_.shutdown(net::tcp::socket::shutdown_both, ignored_ec);
    }
    if (e != async::error::operation_aborted) {
        manager_.stop(shared_from_this());
    }
}
