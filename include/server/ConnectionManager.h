//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_CONNECTIONMANAGER_H
#define SERVER_CONNECTIONMANAGER_H

#include <set>
#include "boost/noncopyable.hpp"
#include "Connection.h"

class ConnectionManager: private boost::noncopyable {
public:
    ConnectionManager();

    void start(std::shared_ptr<Connection> connection);  // add connection to pull
    void stop(std::shared_ptr<Connection> connection);   // close connection and remove from pull
    void stopAll();

    size_t connectionsNumber();

private:
    std::set<std::shared_ptr<Connection>> connections_;
};


#endif  // SERVER_CONNECTIONMANAGER_H
