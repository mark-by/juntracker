//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/AdminAPI.h"

AdminAPI::AdminAPI() {}

std::string AdminAPI::getMainPage(const std::string &str) {
    
}

int AdminAPI::saveCurrentLesson(std::map<std::string, std::string> &group) {
    if (group.empty()) {
        return -1;
    }

    std::string course = group["course"];
    std::string date = group["date"];

    std::map<std::string, std::string>::iterator it = group.begin();

    for (int i = 0; it < group.end(); i++, it++) {
        if (it->first != "lesson" && it->first != "date" ) {
            std::string studentId = it->first;
            std::string status = it->second;

            int res = ManagerVisitHistory.addRecord(course, date, studentId, status);
            if (res) {
                return studentId;
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

int AdminAPI::deleteStudent(const std::vector<string> &str) {
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

int AdminAPI::createStudent(const std::string &str) { // ЧТО СОДЕРЖИТСЯ В СТРОКЕ STR ???
    if (str.empty()) {
        return -1;
    }

    int res = ManagerStudent.addStudent(str);

    if (res) {
        return 1;
    }

    return 0;
}

std::string AdminAPI::getStudentsBy(std::map<std::string, std::string>) {

}

std::string AdminAPI::getPageStudents(int) {

}

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
    if (str.size() == 0) {
        return -1;
    }

    int res = ManagerCourse.deleteCourse(str);

    if (res) {
        return 1;
    }

    return 0;
}

std::string getPaymentsByStudent(const std::string &str) {

}