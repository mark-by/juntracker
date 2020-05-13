//
// Created by gg on 15.04.2020.
//

#include "Connection.h"
#include "ConnectionManager.h"

namespace async = boost::asio;
namespace net = boost::asio::ip;

enum rights {
    admin = 0,
    teacher = 1,
    customer = 2
};

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
        Request request_(std::string(buffer_.begin(), buffer_.end()));
        std::cout << request_.path() << '\n';
        std::cout << request_.method() << '\n';

        if (request_.path() != "/juntracker.ru") {
            std::cout << "some error\n";
        }

        // big switch to choose api for request
        // Response response_;

        /*switch (request_.getRights()) {
            case rights::admin:
                handler_.admin();
                break;
            case rights::teacher:
                handler_.teacher(request_, response_);
                break;
            case rights::customer:
                handler_.customer();
                break;
            default:
                // errorbreak;
        }*/

        // need to write to response_.buffer or something like this
        async::async_write(socket_,
                /*async::buffer(
                        response_.toString().data(),
                        response_.toString().size()
                        ),*/
                async::buffer("shitty reply to client", 24),
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
