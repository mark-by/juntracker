//
// Created by gg on 15.04.2020.
//

#include "Server.h"
#include "boost/bind.hpp"
#include "boost/thread.hpp"
#include <thread>

Server::Server(const std::string &addr, const std::string &port):
    manager_(), service_(), acceptor_(service_), connection_(new Connection(service_, manager_)) {
    net::tcp::resolver resolver_(service_);
    net::tcp::resolver::query query_(addr, port);
    net::tcp::endpoint endpoint_ = *resolver_.resolve(query_);

    acceptor_.open(endpoint_.protocol());
    acceptor_.set_option(net::tcp::acceptor::reuse_address(true));

    acceptor_.bind(endpoint_);
    acceptor_.listen();

    acceptor_.async_accept(
            connection_->socket(),
            boost::bind(
                    &Server::accept,
                    this,
                    async::placeholders::error
            )
    );
}

void Server::startServer() {
    std::vector<std::thread> threads;

    // std::thread::hardware_concurrency() - number of cores
    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++) {
        threads.emplace_back([service = &service_] { service->run();});
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void Server::stopServer() {
    service_.post([this] { stop();});
};

void Server::stop() {
    acceptor_.close();
    manager_.stopAll();
}

void Server::accept(const boost::system::error_code &error) {
    if (!error) {
        manager_.start(connection_);

        connection_.reset(new Connection(service_, manager_));

        acceptor_.async_accept(
                connection_->socket(),
                boost::bind(&Server::accept, this, async::placeholders::error)
        );
    }
}
