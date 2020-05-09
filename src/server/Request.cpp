//
// Created by gg on 15.04.2020.
//

#include "Request.h"
#include <cstring>
#include <iostream>

Request::Request(std::string stringToParse) {

}

std::string Request::getHeader(const std::string &header) {
    return std::string();
}

std::string Request::getPath() {
    return this->path;
}

std::string Request::getData(const std::string &key, std::string returnNotFound) {
    return std::string();
}

std::map<std::string, std::string> Request::parseRequest(const std::string &request) {
    return std::map<std::string, std::string>();
}

std::map<std::string, std::string> Request::parseHeaders(const std::string &request_headers) {
    return std::map<std::string, std::string>();
}

bool Request::init(const std::string &stringToParse) {
    if (stringToParse.find("GET") != std::string::npos) {
        this->method = "GET";
    }
    if (stringToParse.find("POST") != std::string::npos) {
        this->method = "POST";
    }

    size_t start = stringToParse.find("/juntracker.ru");
    size_t end  = stringToParse.find("HTTP");

    this->path = stringToParse.substr(start, end - start);

    return false;
}
