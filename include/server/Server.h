//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "boost/asio.hpp"
#include <string>
#include "ConnectionManager.h"

class Server: private boost::asio::noncopyable {
public:
    Server(const std::string& addr, const std::string& port);  // may added another data to build server
    void startServer();
    void stopServer();

private:
    void accept(const boost::system::error_code& error);  // do async accept
    void stop();  // "handler" to stop Server

    ConnectionManager manager_;

    boost::asio::io_service service_;  // main thing in boost::asio
    boost::asio::ip::tcp::acceptor acceptor_;

    std::shared_ptr<Connection> connection_;
};


#endif //SERVER_SERVER_H
