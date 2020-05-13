//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

#include <string>
#include <unordered_map>
#include "API.h"

class AdminAPI: public API {
public:
    AdminAPI();

    std::string getMainPage(const std::string&);
    int saveCurrentLesson(const std::unordered_map<std::string, std::string> &);//
    std::string findStudent(const std::string&);
    int deleteStudent(const std::vector<std::string>&);//
    int createStudent(const std::unordered_map<std::string, std::string>&);//
    std::string getStudentsBy(std::unordered_map<std::string, std::string>);
    std::string getPageStudents(int);

    int addCourse(const std::string&);//
    int deleteCourse(const std::string&);//

    std::string getPagePaymentsByStudent(const std::string&);

    //NEED TO ADD MORE
};

#endif //CORE_ADMINAPI_H
