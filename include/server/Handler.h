//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>
#include "http/request.h"
#include "http/response.h"
#include "../database/user.h"/*
#include "../core/TeacherAPI.h"
#include "../core/CustomerAPI.h"*/
#include "../core/AdminAPI.h"
#include "../core/UserAPI.h"

class Handler {
public:
    Handler() = default;
    // methods to fill response from request done by Api
    Response teacherHandler(Request request, const User& user);  // handler_.teacher();
    Response adminHandler(Request request, const User& user);    // handler_.adminHandler();
    Response customerHandler(Request request, const User &user); // handler_.customer();
    Response loginHandler(Request request);                      // handle login page

    std::shared_ptr<User> authorizationHandler(Request request); // check login or not

private:
    AdminAPI adminApi;
    UserAPI userApi;
    //TeacherAPI teacherApi;
    //CustomerAPI customerApi;
};


#endif  // SERVER_HANDLER_H
