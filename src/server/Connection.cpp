//
// Created by gg on 15.04.2020.
//

#include"Connection.h"
#include "ConnectionManager.h"
#include "../database/session.h"

namespace async = boost::asio;
namespace net = boost::asio::ip;

Connection::Connection(boost::asio::io_service& service, ConnectionManager& manager):
    socket_(service), manager_(manager), handler_(), buffer_() { };

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
        std::cout << std::string(buffer_.begin(), buffer_.end()) << std::endl;
        Request request_(std::string(buffer_.begin(), buffer_.end()));

        Response response_;

        if (request_.header("Host") != "juntracker.ru") {
            response_.setStatus(status::BadRequest);
        } else {
            if (request_.path() == "/login" || request_.path() == "/register" || request_.path() == "/logout") {
                response_ = handler_.loginHandler(request_);
            } else {
                auto user_ptr = handler_.authorizationHandler(request_);
                if (!user_ptr) {
                    response_ = handler_.customerHandler(request_);
                } else {
                    response_ = handler_.adminHandler(request_, *user_ptr);
                }
            }
        }

        async::async_write(socket_,
                async::buffer(response_.str(), response_.str().max_size()),
                boost::bind(&Connection::doWrite, shared_from_this(),
                        async::placeholders::error));
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
