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
    Handler(Request& req/*, Response& rep*/);
    // methods to fill response from request done by Api
    void teacher();  // handler_.teacher();
    void admin();    // handler_.admin();
    void customer(); // handler_.customer();

    // Response getResponse();

private:
    // AdminApi
    // TeacherAPI tutor;
    // CustomerApi
    Request request_;
    //Response response_;
};


#endif //SERVER_HANDLER_H
