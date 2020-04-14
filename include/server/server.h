//
// Created by gg on 14.04.2020.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "client.h"

class ApiStudent;
class ApiAdmin;

class Server {
public:
    Server(): acceptor_(service_) {}
    void startServer();

private:
    boost::asio::io_service service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    ApiStudent student;  // call methods to create response for client
    ApiAdmin admin;

    void startAccept();
    void onAccept(std::shared_ptr<Client> client,
            const boost::system::error_code& error);
    void run();
};

#endif  // SERVER_SERVER_H
