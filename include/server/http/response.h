#ifndef JUNTRACKER_RESPONSE_H
#define JUNTRACKER_RESPONSE_H

#include <http/request.h>
#include <context/context.h>
#include <unordered_map>
#include <vector>

#define HTTP_VERSION "HTTP/1.1"

namespace status {
    enum statusCode {
        Continue = 100,
        SwitchingProtocol = 101,
        Processing = 102,
        EarlyHints = 103,
        OK = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,
        MultipleChoice = 300,
        MovedPermanently = 301,
        Found = 302,
        SeeOther = 303,
        NotModified = 304,
        BadRequest = 400,
        Unauthorized = 401,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        RequestTimeout = 408,
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502
    };

    std::string statusToStr(int status);
}

class Response {
public:
    Response() = default;
    Response(const Request &request, int status = status::OK);
    Response(const Request &request, const std::string & body, int status = status::OK);
    Response(const std::string & body, int status = status::OK);

    std::string str();
    std::string setCookie(const std::string &key, const std::string &value);
    std::string setHeader(const std::string &key, const std::string &value);
private:
    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> cookies;
    std::string body;
};
#endif //JUNTRACKER_RESPONSE_H
