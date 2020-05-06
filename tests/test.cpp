//
// Created by gg on 15.04.2020.
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.hpp"

// Need realisation to do tests

// test server

int main () {
    try {
        Server server(boost::asio::ip::tcp::v4(), "7777");
        server.startServer();
    } catch (std::exception& err) {
        std::cerr << err.what() << '\n';
    }
}