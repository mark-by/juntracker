//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>
#include "http/request.h"
#include "http/response.h"
//#include "../core/TeacherAPI.h"


class Handler {
public:
    Handler() = default;
    // methods to fill response from request done by Api
    void teacher(const Request& request, Response& response);  // handler_.teacher();
    // Response admin(const Request& request);    // handler_.admin();
    // Response customer(const Request& request); // handler_.customer();

    // Response getResponse();

private:
    // AdminApi
    // TeacherAPI tutor;
    // CustomerApi
};


#endif //SERVER_HANDLER_H
