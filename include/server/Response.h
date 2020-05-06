//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include <string>

enum codes {
    ok = 200,
    page_not_found = 404,
    server_is_down = 500,
};  // like 404 to client

class Response {
public:
    Response();
    Response(std::string request, int status, std::string data = "");
    std::string toString();
    void setBody(std::string data);
    void setHeader(std::string key, std::tring value);  // working with std::map

private:
    std::map<std::string, std::string> headers;
    std::string body;
};

#endif //SERVER_RESPONSE_H