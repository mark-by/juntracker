//
// Created by gg on 15.04.2020.
//

#include "ConnectionManager.h"

ConnectionManager::ConnectionManager() = default;

void ConnectionManager::start(std::shared_ptr<Connection> connection) {
    connections_.insert(connection);
    connection->start();
}

void ConnectionManager::stop(std::shared_ptr<Connection> connection) {
    connections_.erase(connection);
    connection->stop();
}

void ConnectionManager::stopAll() {
    for (auto connection : connections_) {
        connection->stop();
    }
    connections_.clear();
}

size_t ConnectionManager::connectionsNumber() {
    return connections_.size();
}
