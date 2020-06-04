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

    templates::Template _render;

    std::string getMainPage(const User & user) override;
    std::string getPageStudents(const User& user);
    std::string getStudentPage(int student_id, const User& user);

    static int createLesson(const std::unordered_multimap<std::string, std::string> &data, const User &user);
    static int updateLesson(const std::unordered_multimap<std::string, std::string> & data, const User & user);
    static int deleteLesson(int lesson_id);
    static int saveCurrentLesson(const std::unordered_multimap<std::string, std::string> &data);

    static std::pair<int, templates::Context>
    saveStudent(const std::unordered_multimap<std::string, std::string> &data, const User &user);
    static int deleteStudents(const std::unordered_multimap<std::string, std::string> &students, const User& user);
    static templates::Context searchStudent(const std::string &search, const User& user);
    static templates::Context verboseSearchStudent(const std::string &search, const User &user);

    static int editCourse(const std::unordered_multimap<std::string, std::string> &data, const User &user);
    static int deleteCourse(int course_id);

    static int editTeacher(const std::unordered_multimap<std::string, std::string> &data, const User &user);
    static int deleteTeacher(int  teacher_id);

    static int editCabinet(const std::unordered_multimap<std::string, std::string> &data, const User &user);
    static int deleteCabinet(int cabinet_id);

    std::string schedule(const User &user);

    std::string getPagePaymentsByStudent(const std::string &);
private:
    static templates::Context StudentDBSerializer(const Student &student);
    static templates::Context VisitSerializer(const Visit& visit);
    static templates::Context StudentVerboseSerializer(const Student& student);
};

#endif //CORE_ADMINAPI_H
