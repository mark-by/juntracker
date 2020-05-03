//
// Created by gg on 15.04.2020.
//

#include "Handler.h"

Handler::Handler(Request &req, Response &rep):
    request_(std::move(req)), response_(std::move(rep)) {}

void Handler::teacher() {

}

void Handler::admin() {

}

void Handler::customer() {

}
