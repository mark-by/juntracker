//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_REQUEST_H
#define CORE_REQUEST_H

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

#endif //CORE_REQUEST_H
