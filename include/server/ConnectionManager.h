//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_CONNECTIONMANAGER_H
#define SERVER_CONNECTIONMANAGER_H

#include <set>
#include "Connection.h"

class ConnectionManager {
public:
    ConnectionManager();  // create manager

    void start(std::shared_ptr<Connection> connection);
    void stop(std::shared_ptr<Connection> connection);
    void stopAll();

private:
    std::set<std::shared_ptr<Connection>> connections_;  // managed connections
};


#endif //SERVER_CONNECTIONMANAGER_H
