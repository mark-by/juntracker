#include "../../include/core/AdminAPI.h"
#include <context/context.h>
#include <user.h>
#include <lesson.h>
#include <visit.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <http/datetime.h>
#include <utils.hpp>



templates::Context AdminAPI::UserSerializer(const User & user) {
    templates::Context context;
    context.put("username", user.login());
    context.put("isAdmin", true);
    context.putArray("courses", user.get_courses(), SimpleTitleSerializer<Course>());
    context.putArray("teachers", user.get_teachers(), SimplePersonSerializer<Teacher>());
    context.putArray("cabinets", user.get_cabinets(), SimpleTitleSerializer<Cabinet>());
    return context;
}

templates::Context AdminAPI::CurrentLessonSerializer(const Lesson &lesson) {
    templates::Context context;
    context.put("title", lesson.get_course().title());
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
    templates::Context context;
    context.put("name", student.student.name() + " " + student.student.surname());
    context.put("id", student.student.id());
    try {
        bool was = student.student.get_visit(student.lesson.id(),boost::posix_time::second_clock::universal_time()).was_in_class();
        std::cout << "ID NAME: " << student.student.name() << " " << "WAS IN CLASS: " <<  was << std::endl;
        context.put("isHere", was);
    } catch(...) {
        context.put("isHere", false);
    }

    return context;
}

templates::Context AdminAPI::LessonSerializer(const Lesson &lesson) {
    templates::Context context;
    auto course = lesson.get_course();
    context.put("title", course.title());
    context.put("cabinet", lesson.cabinet());
    context.set("cabinet", SimpleTitleSerializer<Cabinet>()(lesson.get_cabinet()));
    context.set("course", SimpleTitleSerializer<Course>()(course));
    context.put("id", lesson.id());
    context.set("teacher", SimplePersonSerializer<Teacher>()(lesson.get_teacher()));
    context.putArray("children", lesson.get_students(), SimplePersonSerializer<Student>());
    context.put("startTime", lesson.start_time());
    context.put("endTime", lesson.end_time());

    return context;
}

templates::Context AdminAPI::DaySerializer(const WeekDay &weekday) {
    templates::Context context;
    context.put("weekDay", weekday.weekday);
    context.put("date", weekday.date);
    context.putArray("lessons", weekday.lessons, LessonSerializer);

    return context;
}

std::string AdminAPI::getMainPage(int userId) {
    templates::Context context;
    auto user = User::get_user(userId);
    context.set("user", UserSerializer(user));
    std::vector<WeekDay> days;
    DateTime dateTime;
    for (int weekday = 0; weekday < 7; weekday++) {
        try {
            days.emplace_back(DateTime::weekdayToStr(weekday), dateTime.dateByWeekday(weekday),
                          user.get_lessons_by_weekday(weekday));
        } catch(...) {}
    }
    context.putArray("scheduleDays", days, DaySerializer);
    std::vector<Lesson> currentLessons;
    try {
        currentLessons = user.get_current_lessons();
    } catch(...) {}
    context.putArray("currentLessons", currentLessons, CurrentLessonSerializer);

    _render.set("mainPageStaff.html");

    return _render.render(context);
}

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

int AdminAPI::createStudent(const std::unordered_multimap<std::string, std::string> &student, const User & user) {
    if (student.empty()) {
        return -1;
    }

    std::string name = student.find("name")->second;
    std::string surname = student.find("surname")->second;
    int age = std::stoi(student.find("age")->second);
    std::string email = student.find("email")->second;
    std::string description = student.find("description")->second;
    std::string telNumber = student.find("tel_number")->second;
    std::string parentName = student.find("parent_name")->second;

    std::string username = randomStr(10);
    User::save(username, randomStr(10), email, Permission::customer, user.school_id());
    auto customer = User::get_user(username);
    Student::save(name, surname, age, customer.id(), description, telNumber, parentName);

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

std::string AdminAPI::getPageStudents(int userId) {
    templates::Context context;
    auto user = User::get_user(userId);
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

int AdminAPI::updateLesson(const std::unordered_multimap<std::string, std::string> &data) {
    if (data.empty()) {
        return 404;
    }
    std::vector<int> students_id;
    for (auto &pair : data) {
        if (pair.first == "student") {
            students_id.push_back(std::stoi(pair.second));
        }
    }

    int lesson_id = std::stoi(data.find("lesson_id")->second);
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
