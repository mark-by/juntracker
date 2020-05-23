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
    std::string teacher(Request request);  // handler_.teacher();
    std::string admin(Request request);    // handler_.admin();
    std::string customer(Request request); // handler_.customer();

private:/*
    AdminAPI admin;
    TeacherAPI tutor;
    CustomerAPI customer;*/
};


#endif //SERVER_HANDLER_H
