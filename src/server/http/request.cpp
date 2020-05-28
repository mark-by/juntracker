#include <http/request.h>
#include <regex>
#include <iostream>
#include <context/context.h>

Request::Request(const std::string &request) {
    std::regex separator(R"(\r*\n\r*\n)");
    std::sregex_iterator separatorMatch(request.cbegin(), request.cend(), separator);
    std::string::const_iterator endHeaders;
    if (separatorMatch->ready()) {
        endHeaders = separatorMatch->suffix().first;
        endHeaders--;
    } else {
        endHeaders = request.cend();
    }
    parseStartLine(request.cbegin(), endHeaders);
    parseHeaders(request.cbegin(), endHeaders);
    parseCookies();
    if (_method == "GET") {
        parseDataFromPath();
    } else if (_method == "POST") {
        parseDataFromBody(endHeaders, request.cend());
    }
}

void Request::parseStartLine(const std::string::const_iterator &begin, const std::string::const_iterator &end){
    const std::regex startLine(R"((PUT|GET|POST|HEAD)\s(/[^\n\s\r\t\0]*)\sHTTP/([\d.]+)\r*\n)");
    std::sregex_iterator match(begin, end, startLine);
    _method = match->format("$1");
    _path = match->format("$2");
}

std::string Request::method() {
    return _method;
}

std::string Request::path() {
    return _path;
}

void Request::parseHeaders(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::regex header(R"(([\w-]+):\s([^\n\r\t\0]+)\r*\n)");
    std::sregex_iterator headerMatch(begin, end, header);
    std::sregex_iterator none;
    while(headerMatch != none) {
        std::string str = headerMatch->str();
        headers.insert({headerMatch->format("$1"), headerMatch->format("$2")});
        headerMatch++;
    }
}

std::string Request::header(const std::string &key) {
    return headers[key];
}

void Request::parseDataFromPath() {
    std::regex separator(R"(\?)");
    std::sregex_iterator separatorMatch(_path.cbegin(), _path.cend(), separator);
    if (!separatorMatch->ready()) {
        return;
    }
    std::regex parameter(R"(([\w-_]+)=([^&\n\r\t\0\s]+))");
    std::sregex_iterator parameterMatch(separatorMatch->suffix().first, _path.cend(), parameter);
    std::sregex_iterator none;
    while (parameterMatch != none) {
        std::string str = parameterMatch->str();
        _data.insert({parameterMatch->format("$1"), parameterMatch->format("$2")});
        parameterMatch++;
    }
    _path = std::string(_path.cbegin(), separatorMatch->prefix().second);
}

void Request::parseDataFromBody(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::string::const_iterator start = begin;
    start++;
    std::string contentType = header("Content-Type");
    if (contentType == "application/x-www-form-urlencoded") {
        std::regex parameter(R"(([^&]+)=([^&]+))");
        std::sregex_iterator parameterMatch(start, end, parameter);
        std::sregex_iterator none;
        while (parameterMatch != none) {
            _data.insert({parameterMatch->format("$1"), parameterMatch->format("$2")});
            parameterMatch++;
        }
    } else if (contentType == "multipart/form-data") {

    } else if (contentType == "text/plain") {
        body = std::string(start, end);
    } else if (contentType == "application/json") {
        std::cout << "HERE" << std::endl;
        std::cout << std::string(start, end);
        templates::Context json(std::string(start, end));
        std::cout << "HERE NOW" << std::endl;
//        _data = json.toMap();
    }
}

std::string Request::data(const std::string &key) {
    return _data[key];
}

std::string Request::data() {
    return body;
}

std::unordered_map<std::string, std::string> Request::dataTable() {
    return _data;
}

void Request::parseCookies() {
    std::string cookiesStr = headers["Cookie"];
    if (cookiesStr.empty()) {
        return;
    }
    std::regex parameter(R"(([^\n\r\t\0\s;]+?)=([^\n\r\t\0\s;]+))");
    std::sregex_iterator parameterMatch(cookiesStr.cbegin(), cookiesStr.cend(), parameter);
    std::sregex_iterator none;
    while(parameterMatch != none) {
        cookies[parameterMatch->format("$1")] = parameterMatch->format("$2");
        parameterMatch++;
    }
}

std::string Request::cookie(const std::string &key) {
    return cookies[key];
}
