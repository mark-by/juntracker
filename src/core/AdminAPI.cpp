#include "../../include/core/AdminAPI.h"
#include <context/context.h>
#include <user.h>
#include <lesson.h>
#include <visit.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <http/datetime.h>

templates::Context AdminAPI::CurrentLessonSerializer(const Lesson &lesson) {
    templates::Context context;
    context.put("title", lesson.get_title());
    context.put("id", lesson.id());
    context.put("cabinet", lesson.cabinet());
    context.put("tutor", lesson.get_teacher().name());
    std::vector<StudentOnLesson> students;
    for (auto &student : lesson.get_students()) {
        students.emplace_back(student, lesson);
    }
    context.putArray("children", students, StudentSerializer);
    context.put("startTime", lesson.start_time());
    context.put("endTime", lesson.end_time());
    return context;
}

templates::Context AdminAPI::StudentSerializer(const StudentOnLesson &student) {
    auto now = boost::posix_time::second_clock();
    templates::Context context;
    context.put("name", student.student.name() + " " + student.student.surname());
    context.put("id", student.student.id());
    context.put("isHere", student.student.get_visit(student.lesson.id(),
                                                    boost::posix_time::second_clock::universal_time()).was_in_class());
    return context;
}

templates::Context AdminAPI::ShortStudentSerializer(const Student &student) {
    templates::Context context;
    context.put("name", student.name() + " " + student.surname());
    return context;
}

templates::Context AdminAPI::LessonSerializer(const Lesson &lesson) {
    templates::Context context;
    context.put("title", lesson.get_title());
    context.put("cabinet", lesson.cabinet());
    context.put("id", lesson.id());
    context.put("tutor", lesson.get_teacher().name());
    context.putArray("children", lesson.get_students(), ShortStudentSerializer);
    context.put("startTime", lesson.start_time());
    context.put("endTime", lesson.end_time());
    return context;
}

templates::Context AdminAPI::DaySerializer(const WeekDay &weekday) {
    templates::Context context;
    context.put("weekDay", weekday.weekday);
    context.put("date", weekday.date);
    context.putArray("lessons", weekday.lessons, LessonSerializer);
}

std::string AdminAPI::getMainPage(int userId) {
    templates::Context context;
    auto user = User::get_user(userId);
    context.put("username", user.login());
    std::vector<WeekDay> days;
    DateTime dateTime;
    for (int weekday = 0; weekday < 7; weekday++) {
        days.emplace_back(dateTime.weekdayToStr(weekday), dateTime.dateByWeekday(weekday),
                          user.get_lessons_by_weekday(weekday));
    }
    context.putArray("scheduleDays", days, DaySerializer);
    auto currentLessons = user.get_current_lessons();
    context.putArray("currentLessons", currentLessons, CurrentLessonSerializer);

    _render.set("mainPageAdmin.html");
    return _render.render(context);
}

int AdminAPI::saveCurrentLesson(const std::unordered_map<std::string, std::string> &data) {
    if (data.empty()) {
        return -1;
    }
    int lesson_id = std::stoi(data.at("lesson_id"));

    for (auto &pair : data) {
        if (pair.first != "check" || pair.first != "lesson_id") {
            Visit::save(std::stoi(pair.first), lesson_id, pair.first == "1");
        }
    }

    return 0;
}

std::string AdminAPI::findStudent(const std::string &str) {
}

int AdminAPI::deleteStudent(int student_id) {
    Student::remove(student_id);
    return 0;
}

int AdminAPI::createStudent(const std::unordered_map<std::string, std::string> &student) {
    if (student.empty()) {
        return -1;
    }

    std::string name = student.at("name");
    std::string surname = student.at("surname");
    int age = std::stoi(student.at("age"));

    Student::save(name, surname, age);

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
        courses.push_back(course.name());
    }
    context.putArray("courses", courses);
    return context;
}

std::string AdminAPI::getPageStudents(int userId) {
    templates::Context context;
    auto user = User::get_user(userId);
    context.put("username", user.login());
    context.put("students", user.get_students(), StudentDBSerializer);
    _render.set("studentsAdmin.html");
    return _render.render(context);
}

int AdminAPI::addCourse(const std::unordered_map<std::string, std::string> &data) {
    auto name = data.at("title");
    int price = std::stoi(data.at("price"));
    Course::save(name, price);
}

int AdminAPI::deleteCourse(int courseId) {
    Course::remove(courseId);
}

std::string AdminAPI::getPagePaymentsByStudent(const std::string &) {
    return std::string();
}
