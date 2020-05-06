//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>
#include "Request.h"
#include "Response.h"

// Response;
// Request

class Handler {
public:
    Handler(Request& req, Response& rep);
    // methods to fill response from request done by Api
    void teacher();  // handler_.teacher();
    void admin();    // handler_.admin();
    void customer(); // handler_.customer();

    // Response getResponse();

private:
    // AdminApi
    // TeacherApi
    // CustomerApi
    Request request_;
    Response response_;
};


#endif //SERVER_HANDLER_H
