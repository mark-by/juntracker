#include <http/request.h>
#include <regex>
#include <iostream>
#include <context/context.h>
#include <boost/algorithm/string.hpp>
#include <curl/curl.h>

Request::Request(const std::string &request) {
    auto __request = urlDecode(request.begin(), request.end());
    std::regex separator(R"(\r*\n\r*\n)");
    std::sregex_iterator separatorMatch(__request.cbegin(), __request.cend(), separator);
    std::string::const_iterator endHeaders;
    if (separatorMatch->ready()) {
        endHeaders = separatorMatch->suffix().first;
        endHeaders--;
    } else {
        endHeaders = __request.cend();
    }
    auto req = std::string(__request.cbegin(), endHeaders);
    parseStartLine(__request.cbegin(), endHeaders);
    parseHeaders(__request.cbegin(), endHeaders);
    parseCookies();
    if (_method == "GET") {
        parseDataFromPath();
    } else if (_method == "POST") {
        parseDataFromBody(endHeaders, __request.cend());
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
        headers.insert({boost::to_lower_copy(headerMatch->format("$1")), headerMatch->format("$2")});
        headerMatch++;
    }
}

std::string Request::header(const std::string &key) {
    auto match =  headers.find(boost::to_lower_copy(key));
    if (match != headers.end()){
        return match->second;
    }
    return "";
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
        std::cout << "here" << std::endl;
        while (parameterMatch != none) {
            std::cout << parameterMatch->format("$1") << " | " <<  parameterMatch->format("$2") << std::endl;
            _data.insert({parameterMatch->format("$1"), parameterMatch->format("$2")});
            parameterMatch++;
        }
        for (auto &pair : _data) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
    } else if (contentType == "multipart/form-data") {

    } else if (contentType == "text/plain") {
        body = std::string(start, end);
    } else if (contentType == "application/json") {
        start++;
        std::string json_str = std::string(start, end);
        boost::trim(json_str);
        std::cout << json_str << std::endl;
        json_str[json_str.size()] = 0;
        templates::Context json(json_str);
        _data = json.toMap();
    }
}

std::string Request::data(const std::string &key) {
    auto search = _data.find(boost::to_lower_copy(key));
    if (search != _data.end()) {
        return search->second;
    }
    return "";
}

std::string Request::data() {
    return body;
}

std::unordered_multimap<std::string, std::string> Request::dataTable() {
    return _data;
}

void Request::parseCookies() {
    std::string cookiesStr = header("Cookie");
    if (cookiesStr.empty()) {
        return;
    }
    std::regex parameter(R"(([^\n\r\t\0\s;]+?)=([^\n\r\t\0\s;]+))");
    std::sregex_iterator parameterMatch(cookiesStr.cbegin(), cookiesStr.cend(), parameter);
    std::sregex_iterator none;
    while(parameterMatch != none) {
        cookies[boost::to_lower_copy(parameterMatch->format("$1"))] = parameterMatch->format("$2");
        parameterMatch++;
    }
}

std::string Request::cookie(const std::string &key) {
    return cookies[boost::to_lower_copy(key)];
}

std::string Request::urlDecode(const std::string& url) {
    CURL *curl = curl_easy_init();
    int outlength;
    char *output = curl_easy_unescape(curl, url.c_str(), url.size(), &outlength);
    auto temp_body = std::string(output);
    curl_free(output);
    curl_easy_cleanup(curl);
    return temp_body;
}

std::string Request::urlDecode(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    return urlDecode(std::string(begin, end));
}
