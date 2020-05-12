#include <http/request.h>
#include <http/response.h>
#include <iostream>

int main() {
    std::string requestStr = "GET /robots.txt?a=34&br=56 HTTP/1.1\n"
                          "Accept: text/html,application/xhtml+xml\n"
                          "Accept-Encoding: gzip, deflate\n"
                          "Cache-Control: max-age=0\n"
                          "Connection: keep-alive\n"
                          "Host: www.ru\n"
                          "User-Agent: Mozilla/5.0 Gecko/20100101 Firefox/39.0";
    Request request(requestStr);
    std::cout << request.method() << std::endl;
    std::cout << request.path() << std::endl;
    std::cout << request.header("Host") << std::endl;
    std::cout << request.data("br") << std::endl;
    std::string postRequestStr = "POST /robots.txt HTTP/1.1\n"
                             "Host: www.ru\n"
                             "User-Agent: Mozilla/5.0 Gecko/20100101 Firefox/39.0\n"
                             "Content-Type: application/x-www-form-urlencoded\n"
                             "\n\n"
                             "field1=value1&field2=value2";
    Request postRequest(postRequestStr);
    std::cout << "POST" << std::endl;
    std::cout << postRequest.data("field2") << std::endl;
    std::string postRequestTextStr = "POST /robots.txt HTTP/1.1\n"
                                 "Host: www.ru\n"
                                 "User-Agent: Mozilla/5.0 Gecko/20100101 Firefox/39.0\n"
                                 "Content-Type: text/plain\n"
                                 "\n\n"
                                 R"({ "some" : 35, "var" : 29 })";
    Request textPlainPost(postRequestTextStr);
    std::cout << "POST text/plain" << std::endl;
    std::cout << textPlainPost.data() << std::endl;
    return 0;
}
