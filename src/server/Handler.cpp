//
// Created by gg on 15.04.2020.
//

#include "Handler.h"

std::string Handler::customer(const Request &request) {
    Response response("<html><h1>Hello world!</h1></html>");
    return response.str();
}

std::string Handler::teacher(const Request &request) {
    return std::string();
}

std::string Handler::admin(const Request &request) {
    return std::string();
}
