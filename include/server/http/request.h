#ifndef JUNTRACKER_REQUEST_H
#define JUNTRACKER_REQUEST_H

#include <string>
#include <unordered_map>

class Request {
public:
    explicit Request(const std::string &request);
    std::string method();
    std::string header(const std::string& key);
    std::string path();
    std::string data(const std::string& key);
    std::string data();
    std::string cookie(const std::string & key);
    std::unordered_map<std::string, std::string> dataTable();

private:
    std::string _method;
    std::string _path;
    std::string body;
    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> _data;
    std::unordered_map<std::string, std::string> cookies;

    void parseStartLine(const std::string::const_iterator &begin, const std::string::const_iterator &end);
    void parseHeaders(const std::string::const_iterator &begin, const std::string::const_iterator &end);
    void parseCookies();
    void parseDataFromPath();
    void parseDataFromBody(const std::string::const_iterator &begin, const std::string::const_iterator &end);
};

#endif //JUNTRACKER_REQUEST_H
