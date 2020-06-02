#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

#include <string>
#include <unordered_map>
#include "API.h"
#include <template/template.h>
#include <user.h>
#include <StaffAPI.h>

class AdminAPI : public StaffAPI {
public:
    AdminAPI() = default;

    int updateLesson(const std::unordered_multimap<std::string, std::string> & data, const User & user);

    static int saveCurrentLesson(const std::unordered_multimap<std::string, std::string> &data);

    std::string findStudent(const std::string &);

    int deleteStudent(int student_id);

    std::string getPageStudents(const User& user);

    int addCourse(const std::unordered_multimap<std::string, std::string> &data, const User &user);

    int deleteCourse(int course_id);

    int addLesson(const std::unordered_multimap<std::string, std::string> &data, const User &user);

    int deleteLesson(const int lesson_id);

    std::string getPagePaymentsByStudent(const std::string &);

    std::pair<int, templates::Context> saveStudent(const std::unordered_multimap<std::string, std::string> &data, const User &user);

    templates::Template _render;

    templates::Context searchStudent(const std::string &search, const User& user);
};

#endif //CORE_ADMINAPI_H
