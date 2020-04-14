//
// Created by gg on 14.04.2020.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <boost/asio.hpp>
#include <iostream>

class Client: std::enable_shared_from_this<Client> {
public:
    explicit Client(boost::asio::io_service& io): clSock(io) {}
    boost::asio::ip::tcp::socket& sock() { return clSock;}
    void read();  // read Response
    void handleRead(const boost::system::error_code& e,
                    std::size_t bytes_transferred);  // write response and continue read

private:
    boost::asio::ip::tcp::socket clSock;
};

#endif  // SERVER_CLIENT_H
