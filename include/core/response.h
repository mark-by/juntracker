//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_RESPONSE_H
#define CORE_RESPONSE_H

class Response {
public:
    Response();
    Response(std::string request, int status, std::string data = "");
    std::string toString();
    void setBody(std::string data);
    void setHeader(std::string key, std::value);

private:
    std::map<std::string, std::string> headers;
    std::string body;
};

#endif //CORE_RESPONSE_H
