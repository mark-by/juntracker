#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

#include <string>
#include <unordered_map>
#include "API.h"
#include <template/template.h>

class AdminAPI: public API {
public:
    AdminAPI() = default;

    std::string getMainPage(int userId);
    int saveCurrentLesson(const std::unordered_map<std::string, std::string> &);
    std::string findStudent(const std::string&);
    int deleteStudent(const std::vector<std::string>&);
    int createStudent(const std::unordered_map<std::string, std::string>&);
    std::string getPageStudents(int);

    int addCourse(const std::string&);
    int deleteCourse(const std::string&);

    std::string getPagePaymentsByStudent(const std::string&);
private:
    templates::Template _render;
};

#endif //CORE_ADMINAPI_H
