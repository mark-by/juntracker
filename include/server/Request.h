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
    std::string getMethod() { return this->method;};
    std::string getHeader(const std::string& header);
    std::string getPath();
    std::string getData(const std::string& key, std::string returnNotFound = "");

private:
    std::string method;
    std::map<std::string, std::string> headers;
    std::string path;

    std::map<std::string, std::string> data;
    std::map<std::string, std::string> parseRequest(const std::string& request);
    std::map<std::string, std::string> parseHeaders(const std::string& headers);
};


#endif //SERVER_REQUEST_H
