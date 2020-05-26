//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>
#include "http/request.h"
#include "http/response.h"
#include "../database/user.h"
//#include "../core/TeacherAPI.h"
//#include "../core/CustomerAPI.h"
#include "../core/AdminAPI.h"

class Handler {
public:
    Handler() = default;
    // methods to fill response from request done by Api
    std::string teacherHandler(Request request, const User& user);  // handler_.teacher();
    std::string adminHandler(Request request, const User& user);  // handler_.adminHandler();
    std::string customerHandler(Request request, const User& user); // handler_.customer();

private:
    AdminAPI admin;
    /*TeacherAPI tutor;
    CustomerAPI customer;*/
};


#endif //SERVER_HANDLER_H
