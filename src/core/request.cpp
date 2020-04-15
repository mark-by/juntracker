//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/request.h"

Request::Request() {}

Request::Request(std::string) {}

std::string Request::getMethod() {}

std::string Request::getHeader(std::string) {}

std::string Request::getPath() {}

std::string Request::getData(std::string key, std::string returnNotFound = "") {}

std::map<std::string, std::string> Request::parseRequest(std::string request) {}

std::map<std::string, std::string> Request::parseHeaders(std::string headers) {}
