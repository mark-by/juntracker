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
