#include <http/request.h>
#include <http/response.h>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>
#include <ctime>

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
    std::cout << postRequest.method() << std::endl;
    std::cout << postRequest.data("field2") << std::endl;
    std::string postRequestTextStr = "POST /robots.txt HTTP/1.1\r\n"
                                 "Host: www.ru\r\n"
                                 "User-Agent: Mozilla/5.0 Gecko/20100101 Firefox/39.0\r\n"
                                 "Content-Type: text/plain\r\n"
                                 "Cookie: session-id=qwpeo=fweoiri; theme=light\r\n"
                                 "\r\n\r\n"
                                 R"({ "some" : 35, "var" : 29 })";
    Request textPlainPost(postRequestTextStr);
    std::cout << "POST text/plain" << std::endl;
    std::cout << textPlainPost.data() << std::endl;
    std::cout << textPlainPost.cookie("session-id") << std::endl;
    std::cout << textPlainPost.cookie("theme") << std::endl;

//    RESPONSE

    std::cout << std::endl;
    Response response;
    response.setHeader("Server", "juntracker");
    response.setCookie("session-id", "ipoirehg98398hifhpwerhg", 1);
    std::cout << response.str() << std::endl;

    templates::Context context;
    context.put("name", "Mark Bykhovets");
    context.put("login", "mark-by");
    Response jsonResponse(context);
    jsonResponse.setHeader("X-Header", "some value");
    jsonResponse.setCookie("theme", "dark");
    jsonResponse.setCookie("session-id", "ipoirehg98398hifhpwerhg", 5);
    jsonResponse.setCookie("csrf-token", "wpeoih34-8h3498h98gh-384h-qj34-f9h-34", 1);
    std::cout << jsonResponse.str() << std::endl;

    std::cout << std::endl;

    std::string htmlText = "<div>Успешно сохранено!</div>";
    Response htmlResponse(htmlText, status::Created);
    htmlResponse.setHeader("X-Header", "some value");
    htmlResponse.setCookie("theme", "dark");
    htmlResponse.setCookie("session-id", "ipoirehg98398hifhpwerhg", 5);
    htmlResponse.setCookie("csrf-token", "wpeoih34-8h3498h98gh-384h-qj34-f9h-34", 1);
    std::cout << htmlResponse.str() << std::endl;
    return 0;
}
