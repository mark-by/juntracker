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
