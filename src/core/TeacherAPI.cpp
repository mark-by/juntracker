//
// Created by timofei on 22.04.2020.
//

#include "../../include/core/TeacherAPI.h"

TeacherAPI::TeacherAPI() {}

std::string TeacherAPI::getMainPage(const std::string &str) {

}

int TeacherAPI::rate(std::unordered_map<std::string, std::string> &group) {
    if (group.empty()) {
        return -1;
    }

    std::string course = group["course"];
    std::string date = group["date"];

    std::map<std::string, std::string>::iterator it = group.begin();

    for (int i = 0; it < group.end(); i++, it++) {
        if (it->first != "lesson" && it->first != "date" ) {
            std::string studentId = it->first;
            std::string mark = it->second;
            int res = ManagerVisitHistory.addRecord(course, date, studentId, mark);

            if (res) {
                return studentId;
            }
        }
    }
}