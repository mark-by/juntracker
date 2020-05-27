#include <http/response.h>

void Response::setCookie(const std::string &key, const std::string &value, const int &daysExpires) {
    std::string _value = value;
    if (daysExpires) {
        auto now = boost::posix_time::second_clock::universal_time();
        _value += ";" + (" Expires=" + ptimeConverter.convert(now + boost::gregorian::days(daysExpires)));
    }
    cookies[key] = _value;
}

void Response::setDate() {
    auto now = boost::posix_time::second_clock::universal_time();
    headers.insert({"Date", ptimeConverter.convert(now)});
}

Response::Response(const templates::Context &jsonData, const int &status) : statusCode(status) {
    setDate();
    setHeader("Content-Type", "application/json");
    body = jsonData.str();
    setHeader("Content-Length", std::to_string(body.size()));
}

Response::Response(const int &status) : statusCode(status) {
    setDate();
}

void Response::startLineToStream(std::stringstream & ss) {
    ss << HTTP_VERSION << " " << statusCode << " " << statusToStr() << "\r\n";
}

std::string Response::str() {
    std::stringstream response;
    startLineToStream(response);
    headersToStream(response);
    cookiesToStream(response);
    response << "\r\n";
    response << body;
    return response.str();
}

Response::Response(const std::string &html, const int &status) : statusCode(status) {
    setDate();
    setHeader("Content-Type", "text/html; charset=UTF-8");
    body = html;
    setHeader("Content-Length", std::to_string(body.size()));
}

void Response::headersToStream(std::stringstream & ss) {
    for (auto &pair : headers) {
        ss << pair.first << ": " << pair.second << "\r\n";
    }
}


void Response::cookiesToStream(std::stringstream &ss) {
    for (auto &pair : cookies) {
        ss << "Set-Cookie: " << pair.first << "=" << pair.second << "\r\n";
    }
}

void Response::setHeader(const std::string &key, const std::string &value) {
    headers.insert({key, value});
}

std::string Response::statusToStr() const {
    switch(statusCode) {
        case (100): return "Continue";
        case (101): return "Switching Protocol";
        case (102): return "Processing";
        case (103): return "Early Hints";
        case (200): return "OK";
        case (201): return "Created";
        case (202): return "Accepted";
        case (204): return "No Content";
        case (300): return "Multiple Choice";
        case (301): return "Moved Permanently ";
        case (302): return "Found";
        case (304): return "Not Modified";
        case (400): return "Bad Request";
        case (401): return "Unauthorized ";
        case (403): return "Forbidden";
        case (404): return "NotFound";
        case (405): return "Method Not Allowed";
        case (408): return "Request Timeout";
        case (500): return "Internal Server Error";
        case (501): return "Not Implemented";
        case (502): return "Bad Gateway";
        default: return "undefined";
    }
}

Response &Response::operator=(const Response &other) {
    headers = other.headers;
    cookies = other.cookies;
    body = other.body;
    statusCode = other.statusCode;
    return *this;
}

void Response::setStatus(const int &status) {
    statusCode = status;
}
