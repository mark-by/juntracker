//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H

#include <string>
#include <map>

class Request {
public:
    Request() = default;
    Request(std::string);
    std::string getMethod() { return this->method;};
    std::string getHeader(const std::string& header);
    // header like
    std::string getPath();  // url from request
    std::string getData(const std::string& key, std::string returnNotFound = "");

private:
    std::string method;  // GET or POST
    std::map<std::string, std::string> headers;
    std::string path;  // url

    std::map<std::string, std::string> data;  // data like persons [{"name": "John" "surname": "Smith"},]
    std::map<std::string, std::string> parseRequest(const std::string& request);  // call in constructor
    std::map<std::string, std::string> parseHeaders(const std::string& headers);  // call in constructor
};


#endif //SERVER_REQUEST_H
