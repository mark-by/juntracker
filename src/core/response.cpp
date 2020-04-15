//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/response.h"

Response::Response() {}

Response::Response(std::string request, int status, std::string data = "") {}

std::string Response::toString() {}

void Response::setBody(std::string data) {}

void Response::setHeader(std::string key, std::value) {}