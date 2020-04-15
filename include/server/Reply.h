//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_REPLY_H
#define SERVER_REPLY_H

#include <string>

struct Header {
    std::string name;
    std::string value;
};

struct Reply {
    enum codes {

    };  // like 404 to client

    std::vector<Header> headers;

    std::string content;
};  // improve in future

#endif //SERVER_REPLY_H
