#include "../../include/core/AdminAPI.h"
#include <day.h>
#include <context/context.h>
#include <user.h>
#include <lesson.h>
#include <visit.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <http/datetime.h>

templates::Context StudentSerializer(const Student & student) {
    auto now = boost::posix_time::second_clock();
    templates::Context context;
    context.put("name", student.get_name() + " " + student.get_surname());
    context.put("id", student.id());
    context.put("isHere", student.get_visit(boost::posix_time::second_clock::universal_time()).was_is_class());
    return context;
}

templates::Context ShortStudentSerializer(const Student & student) {
   templates::Context context;
   context.put("name", student.get_name() + " " + student.get_surname());
   return context;
}

templates::Context LessonSerializer(const Lesson & lesson) {
    templates::Context context;
    context.put("title", lesson.get_title());
    context.put("cabinet", lesson.cabinet());
    context.put("tutor", lesson.get_teacher().name());
    context.putArray("children", lesson.get_students(), ShortStudentSerializer);
    context.put("startTime", lesson.get_start_time());
    context.put("endTime", lesson.get_end_time());
}

templates::Context CurrentLessonSerializer(const Lesson & lesson) {
    templates::Context context;
    context.put("title", lesson.get_title());
    context.put("cabinet", lesson.cabinet());
    context.put("tutor", lesson.get_teacher().name());
    context.putArray("children", lesson.get_students(), StudentSerializer);
    context.put("startTime", lesson.get_start_time());
    context.put("endTime", lesson.get_end_time());
}

struct WeekDay {
    std::string weekday;
    std::string date;
    std::vector<Lesson> lessons;
};

templates::Context DaySerializer(const WeekDay & weekday) {
    templates::Context context;
    context.put("weekDay", weekday.weekday);
    context.put("date", weekday.date);
    context.putArray("lessons", weekday.lessons, LessonSerializer);
}

std::string AdminAPI::getMainPage(int userId) {
    templates::Context context;
    auto user = User::get_user(userId);
    context.put("username", user.username);
    std::vector<WeekDay> days;
    DateTime dateTime;
    for (int weekday = 0; weekday < 7; weekday++) {
        days.emplace_back(dateTime.weekdayToStr(weekday), dateTime.dateByWeekday(weekday), user.get_lessons_by_weekday(weekday));
    }
    context.putArray("scheduleDays", days, DaySerializer);
    auto currentLessons = user.get_current_lessons();
    context.putArray("currentLessons", currentLessons, CurrentLessonSerializer);

    _render.set("mainPageAdmin.html");
    return _render.render(context);
}

int AdminAPI::saveCurrentLesson(const std::unordered_map<std::string, std::string> &group) {
    if (group.empty()) {
        return -1;
    }

    std::string course = group.at("course");
    std::string date = group.at("date");

    auto it = group.begin();

    for (int i = 0; it < group.end(); i++, it++) {
        if (it->first != "lesson" && it->first != "date" ) {
            std::string studentId = it->first;
            std::string status = it->second;
            int res = ManagerVisitHistory.addRecord(course, date, studentId, status);

            if (res) {
                return std::stoi(studentId);
            }
        }
    }

    return 0;
}

std::string AdminAPI::findStudent(const std::string &str) {
    /*if (str.size() == 0) {
        return
    }

    std::vector<std::string> result = ManagerStudent.fingStudentBy();*/
}

int AdminAPI::deleteStudent(const std::vector<std::string> &str) {
    if (str.empty()) {
        return -1;
    }

    std::vector<std::string>::iterator it = str.begin();

    while (it != str.end()) {
        int res = str.deleteStudent(it);
        if (res) {
            return (it);
        }
        it++;
    }

    return 0;
}

int AdminAPI::createStudent(const std::unordered_map<std::string, std::string> &student) {
    if (student.empty()) {
        return -1;
    }

    std::string name = student["name"];
    std::string surname = student["surname"];
    std::string age = student["age"];

    int res = ManagerStudent.addStudent(name, surname, age);

    if (res) {
        return 1;
    }

    return 0;
}

std::string AdminAPI::getStudentsBy(std::unordered_map<std::string, std::string>) {
    return std::string();
}

std::string AdminAPI::getPageStudents(int) {

}

int AdminAPI::addCourse(const std::string &) {
    return 0;
}

int AdminAPI::deleteCourse(const std::string &) {
    return 0;
}

std::string AdminAPI::getPagePaymentsByStudent(const std::string &) {
    return std::string();
}

*/

int addCourse(const std::string &str) {
    if (str.empty()) {
        return -1;
    }

    int res = ManagerCourse.addCourse(str);

    if (res) {
        return 1;
    }

    return 0;
}

int deleteCourse(const std::string &str) {
    if (str.empty()) {
        return -1;
    }

    int res = ManagerCourse.deleteCourse(str);

    if (res) {
        return 1;
    }

    return 0;
}

/*
std::string getPagePaymentsByStudent(const std::string &studentId) {
    if (studentId.empty()) {
        return "NULL";
    }

    std::vector<Payment> paymentHistory = ManagerPaymentHistory.getPaymentHistory(studentId);
    templates::Context context;

    context.putArray(paymentHistory, paymentSerializer);

    template.set("payments.html");

    return template.render(context);
}*/
