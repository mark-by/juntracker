//
// Created by gg on 15.04.2020.
//

#include "Server.h"

Server::Server(const std::string &addr, const std::string &port):
        io_context_(), acceptor_(io_context_), manager_(),
        connection_(new Connection(io_context_, manager_, handler_)), handler_() {

}
