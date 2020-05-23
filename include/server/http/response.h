#ifndef JUNTRACKER_RESPONSE_H
#define JUNTRACKER_RESPONSE_H

#include <context/context.h>
#include <unordered_map>
#include <vector>
#include <http/datetime.h>
#include <context/context.h>

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

}

class Response {
public:
    explicit Response(const int &status = status::OK);
    explicit Response(const std::string & html, const int &status = status::OK);
    explicit Response(const templates::Context & jsonData, const int &status = status::OK);

    std::string str();
    void setCookie(const std::string &key, const std::string &value, const int &daysExpires = 0);
    void setHeader(const std::string &key, const std::string &value);
private:
    void setDate();
    std::string statusToStr() const;
    void startLineToStream(std::stringstream & ss);
    void headersToStream(std::stringstream & ss);
    void cookiesToStream(std::stringstream & ss);

    DateTimeConverter ptimeConverter;
    std::unordered_multimap<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> cookies;
    std::string body;
    int statusCode;
};
#endif //JUNTRACKER_RESPONSE_H
