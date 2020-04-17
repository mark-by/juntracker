//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include <string>

struct Header {
    std::string name;
    std::string value;
};

struct Response {
    enum codes {

    };  // like 404 to client

    std::vector<Header> headers;

    std::string content;
};  // improve in future

#endif //SERVER_RESPONSE_H
