//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H

#include <string>
#include <map>

class Request {
public:
    Request();
    Request(std::string);
    std::string getMethod();
    std::string getHeader(std::string);
    std::string getPath();
    std::string getData(std::string key, std::string returnNotFound = "");

private:
    std::string method;
    std::map<std::string, std::string> headers;
    std::string path;
    std::string body;
    std::map<std::string, std::string> data;
    std::map<std::string, std::string> parseRequest(std::string request);
    std::map<std::string, std::string> parseHeaders(std::string headers);
};


#endif //SERVER_REQUEST_H
