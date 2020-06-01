#include "../../include/core/AdminAPI.h"
#include <context/context.h>
#include <user.h>
#include <lesson.h>
#include <visit.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <utils.hpp>

int AdminAPI::saveCurrentLesson(const std::unordered_multimap<std::string, std::string> &data) {
    if (data.empty()) {
        return 400;
    }
    int lesson_id = std::stoi(data.find("lesson_id")->second);

    for (auto &pair : data) {
        if (pair.first != "check" && pair.first != "lesson_id") {
            Visit::save(std::stoi(pair.first), lesson_id, pair.second[0] == '1');
        }
    }

    return 200;
}

std::string AdminAPI::findStudent(const std::string &str) {

    return std::string();
}

int AdminAPI::deleteStudent(int student_id) {
    Student::remove(student_id);

    return 0;
}

templates::Context StudentDBSerializer(const Student &student) {
    templates::Context context;
    context.put("name", student.name() + " " + student.surname());
    context.put("avatar", "");
    context.put("id", student.id());
    context.put("age", student.age());
    std::vector<std::string> courses;
    for (auto &course : student.get_courses()) {
        courses.push_back(course.title());
    }
    context.putArray("courses", courses);

    return context;
}

std::string AdminAPI::getPageStudents(const User &user) {
    templates::Context context;
    context.put("username", user.login());
    context.putArray("students", user.get_students(), StudentDBSerializer);
    _render.set("studentsAdmin.html");

    return _render.render(context);
}

int AdminAPI::addCourse(const std::unordered_multimap<std::string, std::string> &data, const User &user) {
    auto name = data.find("title")->second;
    int price = std::stoi(data.find("price")->second);
    int teacher_id = std::stoi(data.find("teacher_id")->second);
    Course::save(name, price, user.school_id(), teacher_id);

    return 0;
}

int AdminAPI::deleteCourse(int courseId) {
    Course::remove(courseId);

    return 0;
}

std::string AdminAPI::getPagePaymentsByStudent(const std::string &) {
    return std::string();
}

int AdminAPI::updateLesson(const std::unordered_multimap<std::string, std::string> &data, const User& user) {
    if (data.empty()) {
        return 404;
    }

    int lesson_id = std::stoi(data.find("lesson_id")->second);
    std::vector<int> students_id;
    for (auto &pair : data) {
        if (pair.first == "new_student") {
            Lesson::add_student(std::stoi(pair.second), lesson_id);
        } else if (pair.first == "delete_student") {
            Lesson::delete_student(std::stoi(pair.second), lesson_id);
        }
    }

    auto lesson = Lesson::get_lesson(lesson_id);
    lesson.update(lesson_id,
                  std::stoi(data.find("course")->second),
                  std::stoi(data.find("cabinet")->second),
                  std::stoi(data.find("teacher")->second),
                  std::stoi(data.find("weekday")->second),
                  data.find("start-hours")->second + ":" + data.find("start-minutes")->second,
                  data.find("end-hours")->second + ":" + data.find("end-minutes")->second,
                  lesson.school_id());
    auto students = lesson.get_students();

    return 200;
}



std::pair<int, templates::Context> AdminAPI::saveStudent(const std::unordered_multimap<std::string, std::string> &student, const User &user) {
    templates::Context context;

    if (student.empty()) {
        return {404, context};
    }

    std::string result;
    bool success;
    std::tie(result, success) = fetch("name", student);
    if (!success) return {404, context};
    auto name = result;
    std::tie(result, success) = fetch("surname", student);
    if (!success) return {404, context};
    auto surname = result;
    int age = std::stoi(get("age", student));
    auto description = get("description", student);
    auto tel_number = get("tel_number", student);
    auto email = get("email", student);
    auto parent = get("parent", student);
    auto avatar = get("avatar", student);

    int school_id = user.school_id();

    int id = Student::save(name, surname, age, description, tel_number, email, parent, avatar, school_id);
    context.put("id", id);

    return {200, context};
}
