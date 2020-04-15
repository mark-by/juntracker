//
// Created by gg on 15.04.2020.
//

#ifndef SERVER_REQUESTHANDLER_H
#define SERVER_REQUESTHANDLER_H

#include <string>

struct Reply;
// Request

class RequestHandler {
public:
    std::string requestToCore(/*"parsed" request*/);

private:
    // Request
};


#endif //SERVER_REQUESTHANDLER_H
