//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>
#include "http/request.h"
#include "http/response.h"/*
#include "../core/TeacherAPI.h"
#include "../core/CustomerAPI.h"
#include "../core/AdminAPI.h"*/

class Handler {
public:
    Handler() = default;
    // methods to fill response from request done by Api
    std::string teacher(const Request& request);  // handler_.teacher();
    std::string admin(const Request& request);    // handler_.admin();
    std::string customer(const Request& request); // handler_.customer();

    // Response getResponse();

private:/*
    AdminAPI admin;
    TeacherAPI tutor;
    CustomerAPI customer;*/
};


#endif //SERVER_HANDLER_H
