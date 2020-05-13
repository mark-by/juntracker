//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/AdminAPI.h"

AdminAPI::AdminAPI() {}

/*std::string AdminAPI::getMainPage(const std::string &str) {

}*/

int AdminAPI::saveCurrentLesson(const std::unordered_map<std::string, std::string> &group) {
    if (group.empty()) {
        return -1;
    }

    std::string course = group["course"];
    std::string date = group["date"];

    std::unordered_map<std::string, std::string>::iterator it = group.begin();

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

/*std::string AdminAPI::getStudentsBy(std::unordered_map<std::string, std::string>) {

}

std::string AdminAPI::getPageStudents(int) {

}*/

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
