# Core

Ссылка на UML https://www.figma.com/file/rU0ysrN3E5T0DkiTUlxiW7/MindMap-JunTracker?node-id=0%3A1

AdminAPI:
	getPageMain(std::string): std::string - получить данные для рендера главной страницы
	saveCurrentLesson(std::map<std::string, std::string>): int - сохранить данные о посещаемости на занятии
	findStudent(std::string str): std::string - возвращает список студентов, чье имя начинается на str
	deleteStudent(std::vector<string>): int  - удалить студентов из базы
	createStudent(std::string): int - добавить студента в базу
	getStudentsBy(std::map<std::string, std::string>): string - возвращает список учеников, удовл критерию
	getPageStudents(int): std::string - пагинация студентов
	
	

CustomerAPI:
	getPageMain(std::string): std::string - получает расписание на ближайшие 7 учебных дней и оценки

TeacherAPI:
	getPageMain(std::string): std::string - 
	rate(std::string): int - поставить оценку ученику по предмету за опр дату.
=======
# SqlWrapper

Обёртка над библиотекой работы с базой данных.
=======
# HTMLTemplate

## Context example (out)
```json
{
    "name": "Mark Bykhovets",
    "obj": {
        "value1": "1",
        "value2": "2"
    },
    "array": [
        "1",
        "5",
        "3",
        "4",
        "6"
    ],
    "vector_array": [
        "65",
        "4",
        "3",
        "45",
        "6",
        "65"
    ],
    "person": [
        {
            "name": "Josh",
            "second_name": "Brown",
            "age": "20"
        },
        {
            "name": "Homer",
            "second_name": "Simpson",
            "age": "31"
        },
        {
            "name": "Ragnar",
            "second_name": "Lodbrok",
            "age": "25"
        }
    ]
}
OUT
2
1 5 3 4 6 
{
    "name": "Josh",
    "second_name": "Brown",
    "age": "20"
}
{
    "name": "Homer",
    "second_name": "Simpson",
    "age": "31"
}
{
    "name": "Ragnar",
    "second_name": "Lodbrok",
    "age": "25"
}
```
## Template example  
```
template.html
-------------------------
{% extends base.html %}

{% block title %}
Test Title
{% endblock %}

{% block main %}
<article>Some content</article>
{% endblock %}


base.html
---------------------
<html>
<head>
    <title>{% block title %}Title undefined{% endblock %}</title>
</head>
<body>
{% include logo.html %}
<main>
    {% if b %}
    <div>if b</div>
    {% else %}
    <div>else if b</div>
    {% endif %}
    {% for i in array %}
        <div>Printed:{{ var }}and{{ i }}</div>
        {% for j in jarray %}
            <span>print {{ j }}</span>
        {% endfor %}
    {% endfor %}

    {% block main %}
    {% endblock %}
</main>
</body>
</html>


example.cpp
---------------------------------
#include <iostream>
#include <template/template.h>

int main() {
    std::string filename = "template.html";
    std::string settings_path = "../../test/templates_test/test_files/settings";
    templates::Template templ(settings_path);
    templates::Context context;
    context.put("b", true);
    context.put("var", 35585);
    context.putArray("array", std::vector<int>{1,2,3,4});
    context.putArray("jarray", std::vector<int>{55, 66, 77});
    templ.set(filename);
    std::cout << templ.render(context) << std::endl;
    return 0;
}

result.html
-------------------------------------------
<html><head><title>Test Title</title></head><body><div class="LOGO">SOME LOGO</div><div class="LOGO">SOME LOGO</div><div class="LOGO">SOME LOGO</div><div class="LOGO">SOME LOGO</div><main><div>if b</div><div>Printed: 35585 and 1</div><span>print 55</span><span>print 66</span><span>print 77</span><div>Printed: 35585 and 2</div><span>print 55</span><span>print 66</span><span>print 77</span><div>Printed: 35585 and 3</div><span>print 55</span><span>print 66</span><span>print 77</span><div>Printed: 35585 and 4</div><span>print 55</span><span>print 66</span><span>print 77</span><article>Some content</article></main></body></html>
```

#объекты Request and Response пример
**http_example.cpp**
```
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
```
**Вывод:**
```
GET
/robots.txt
www.ru
56
POST
value2
POST text/plain
{ "some" : 35, "var" : 29 }
qwpeo=fweoiri
light

HTTP/1.1 200 OK
Date: Wed, 13 May 2020 02:08:45 GMT
Server: juntracker
Set-Cookie: session-id=ipoirehg98398hifhpwerhg; Expires=Thu, 14 May 2020 02:08:45 GMT



HTTP/1.1 200 OK
Content-Length: 57
Date: Wed, 13 May 2020 02:08:45 GMT
X-Header: some value
Content-Type: application/json
Set-Cookie: csrf-token=wpeoih34-8h3498h98gh-384h-qj34-f9h-34; Expires=Thu, 14 May 2020 02:08:45 GMT
Set-Cookie: theme=dark
Set-Cookie: session-id=ipoirehg98398hifhpwerhg; Expires=Mon, 18 May 2020 02:08:45 GMT


{
    "name": "Mark Bykhovets",
    "login": "mark-by"
}


HTTP/1.1 201 Created
Content-Length: 45
Date: Wed, 13 May 2020 02:08:45 GMT
X-Header: some value
Content-Type: text/html
Set-Cookie: csrf-token=wpeoih34-8h3498h98gh-384h-qj34-f9h-34; Expires=Thu, 14 May 2020 02:08:45 GMT
Set-Cookie: theme=dark
Set-Cookie: session-id=ipoirehg98398hifhpwerhg; Expires=Mon, 18 May 2020 02:08:45 GMT


<div>Успешно сохранено!</div>
```