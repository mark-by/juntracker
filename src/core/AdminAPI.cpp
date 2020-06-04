#include <AdminAPI.h>
#include <context/context.h>
#include <user.h>
#include <lesson.h>
#include <visit.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <utils.hpp>


std::string AdminAPI::getMainPage(const User &user) {
    auto context = mainStaffData(user);
    context.putArray("teachers", user.get_teachers(), PersonSerializer<Teacher>());
    context.putArray("courses", user.get_courses(), CourseSerializer);
    context.putArray("cabinets", user.get_cabinets(), SimpleTitleSerializer<Cabinet>());
    _render.set("mainPageStaff.html");

    return _render.render(context);
}

std::string AdminAPI::getPageStudents(const User &user) {
    templates::Context context;
    context.set("user", UserSerializer(user));
    context.putArray("students", user.get_students(), StudentDBSerializer);
    _render.set("students.html");

    return _render.render(context);
}

std::string AdminAPI::getStudentPage(int student_id, const User& user) {
    templates::Context context;
    auto student = Student::get_student(student_id);
    context.set("student", StudentVerboseSerializer(student));
    context.set("user", UserSerializer(user));
    _render.set("student.html");
    return _render.render(context);
}

int AdminAPI::createLesson(const std::unordered_multimap<std::string, std::string> &lesson, const User &user) {
    templates::Context context;

    if (lesson.empty()) {
        return 404;
    }

    std::string result;
    bool success;
    std::tie(result, success) = fetch("teacher", lesson);
    if (!success)
        return 404;
    int teacher_id = std::stoi(result);
    std::tie(result, success) = fetch("course", lesson);
    if (!success)
        return 404;
    int course_id = std::stoi(result);
    std::tie(result, success) = fetch("cabinet", lesson);
    if (!success)
        return 404;
    int cabinet_id = std::stoi(result);

    int weekday = std::stoi(get("weekday", lesson));
    auto start_time = get("start-hours", lesson) + ":" + get("start-minutes", lesson);
    auto end_time = get("end-hours", lesson) + ":" + get("end-minutes", lesson);
    int school_id = user.school_id();

    int lesson_id = Lesson::save(course_id, cabinet_id, teacher_id, weekday, start_time, end_time, school_id);

    for (auto &pair : lesson) {
        if (pair.first == "new_student") {
            Lesson::add_student(std::stoi(pair.second), lesson_id, course_id);
        } else if (pair.first == "delete_student") {
            Lesson::delete_student(std::stoi(pair.second), lesson_id, course_id);
        }
    }

    return 200;
}

int AdminAPI::updateLesson(const std::unordered_multimap<std::string, std::string> &data, const User &user) {
    if (data.empty()) {
        return 404;
    }

    int lesson_id = std::stoi(get("lesson_id", data));
    int course_id = std::stoi(get("course", data));
    std::vector<int> students_id;
    for (auto &pair : data) {
        if (pair.first == "new_student") {
            Lesson::add_student(std::stoi(pair.second), lesson_id, course_id);
        } else if (pair.first == "delete_student") {
            Lesson::delete_student(std::stoi(pair.second), lesson_id, course_id);
        }
    }

    auto lesson = Lesson::get_lesson(lesson_id);
    lesson.update(lesson_id,
                  std::stoi(get("course", data)),
                  std::stoi(get("cabinet", data)),
                  std::stoi(get("teacher", data)),
                  std::stoi(get("weekday", data)),
                  get("start-hours", data) + ":" + get("start-minutes", data),
                  get("end-hours", data) + ":" + get("end-minutes", data),
                  lesson.school_id());
    auto students = lesson.get_students();

    return 200;
}

int AdminAPI::deleteLesson(int lesson_id) {
    Lesson::remove(lesson_id);

    return 200;
}

int AdminAPI::saveCurrentLesson(const std::unordered_multimap<std::string, std::string> &data) {
    if (data.empty()) {
        return 400;
    }

    int lesson_id = std::stoi(get("lesson_id", data));

    for (auto &pair : data) {
        if (pair.first != "check" && pair.first != "lesson_id") {
            Visit::save(std::stoi(pair.first), lesson_id, pair.second[0] == '1');
        }
    }

    return 200;
}

std::pair<int, templates::Context>
AdminAPI::saveStudent(const std::unordered_multimap<std::string, std::string> &student, const User &user) {
    templates::Context context;

    if (student.empty()) {
        return {404, context};
    }

    std::string result;
    bool success;
    std::tie(result, success) = fetch("name", student);
    if (!success)
        return {404, context};
    auto name = result;
    std::tie(result, success) = fetch("surname", student);
    if (!success)
        return {404, context};
    auto surname = result;
    auto res = get("age", student);
    int age = res.empty() ? 0 : std::stoi(res);
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

int AdminAPI::deleteStudents(const std::unordered_multimap<std::string, std::string> &students, const User &user) {
    for (auto &pair : students) {
        if (pair.first == "id")
            Student::remove(std::stoi(pair.second));
    }

    return 200;
}

templates::Context AdminAPI::searchStudent(const std::string &search, const User &user) {
    templates::Context context;
    auto students = Student::get_students_like(search, user.school_id());
    context.putArray("students", students, SimplePersonSerializer<Student>());

    return context;
}

templates::Context AdminAPI::verboseSearchStudent(const std::string &search, const User &user) {
    templates::Context context;
    auto students = Student::get_students_like(search, user.school_id());
    context.putArray("students", students, StudentDBSerializer);

    return context;
}

int AdminAPI::editCourse(const std::unordered_multimap<std::string, std::string> &data, const User &user) {
    if (data.empty()) {
        return 404;
    }

    std::string result;
    bool success;
    std::tie(result, success) = fetch("title", data);
    if (!success)
        return 404;
    auto name = result;

    std::tie(result, success) = fetch("price", data);
    if (!success)
        return 404;
    int price = std::stoi(result);

    std::tie(result, success) = fetch("id", data);
    if (!success)
        return 404;
    int id = std::stoi(result);

    if (id == -1) {
        Course::save(name, price, user.school_id());
    } else {
        Course::update(id, name, price, user.school_id());
    }

    return 200;
}

int AdminAPI::deleteCourse(int courseId) {
    try {
        Course::remove(courseId);
        return 200;
    } catch(...) {
        return 400;
    }
}

int AdminAPI::editTeacher(const std::unordered_multimap<std::string, std::string> &data, const User &user) {
    if (data.empty()) {
        return 404;
    }

    std::string result;
    bool success;
    std::tie(result, success) = fetch("name", data);
    if (!success)
        return 404;
    auto name = result;
    std::tie(result, success) = fetch("surname", data);
    if (!success)
        return 404;
    auto surname = result;
    std::tie(result, success) = fetch("id", data);
    if (!success)
        return 404;
    int id = std::stoi(result);

    int school_id = user.school_id();

    if (id == -1) {
        Teacher::save(name, surname, school_id);
    } else {
        Teacher::update(id, name, surname);
    }

    return 200;
}

int AdminAPI::deleteTeacher(int teacher_id) {
    Teacher::remove(teacher_id);

    return 200;
}

int AdminAPI::editCabinet(const std::unordered_multimap<std::string, std::string> &data, const User &user) {
    if (data.empty()) {
        return 404;
    }

    std::string result;
    bool success;
    std::tie(result, success) = fetch("name", data);
    if (!success)
        return 404;
    auto title = result;

    std::tie(result, success) = fetch("id", data);
    if (!success)
        return 404;
    int id = std::stoi(result);

    int school_id = user.school_id();

    if (id == -1) {
        Cabinet::save(title, school_id);
    } else {
        Cabinet::update(title, school_id, id);
    }

    return 200;
}

int AdminAPI::deleteCabinet(int cabinet_id) {
    Cabinet::remove(cabinet_id);

    return 200;
}

std::string AdminAPI::schedule(const User &user) {
    auto context = mainScheduleStaffData(user);
    context.putArray("teachers", user.get_teachers(), PersonSerializer<Teacher>());
    context.putArray("courses", user.get_courses(), CourseSerializer);
    context.putArray("cabinets", user.get_cabinets(), SimpleTitleSerializer<Cabinet>());
    _render.set("scheduleStaff.html");
    return _render.render(context);
}

std::string AdminAPI::getPagePaymentsByStudent(const std::string &) {
    return std::string();
}

templates::Context AdminAPI::StudentDBSerializer(const Student &student) {
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

templates::Context AdminAPI::VisitSerializer(const Visit& visit) {
    templates::Context context;
    auto lesson = visit.get_lesson();
    context.put("wasInClass", visit.was_in_class());
    context.put("course", lesson.get_course().title());
    context.put("weekday", DateTime::weekdayToStr(lesson.weekday()));
    context.put("date", visit.date());

    return context;
}

templates::Context AdminAPI::StudentVerboseSerializer(const Student& student) {
    templates::Context context;
    context.put("id", student.id());
    context.put("name", student.name());
    context.put("surname", student.surname());
    context.put("avatar", student.avatar());
    context.put("age", student.age());
    context.put("parent", student.parent());
    context.put("telNumber", student.tel_number());
    context.put("email", student.email());
    context.put("description", student.description());
    context.putArray("visits", student.get_visits(), VisitSerializer);

    return context;
}


