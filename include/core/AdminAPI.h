#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

#include <string>
#include <unordered_map>
#include "API.h"
#include <template/template.h>
#include <user.h>
#include <StaffAPI.h>

class AdminAPI : public StaffAPI {
    struct VerboseStudent {
        int id;
        int age;
        std::string name;
        std::vector<std::string> courses;
        std::string avatar;

        VerboseStudent(int id, int age, const std::string &name, const std::string &avatar, const std::vector<std::string>& courses) :
                id(id), age(age), name(name), courses(courses), avatar(avatar) {}
    };
public:
    AdminAPI() = default;

    int updateLesson(const std::unordered_multimap<std::string, std::string> & data, const User & user);

    static int saveCurrentLesson(const std::unordered_multimap<std::string, std::string> &data);

    std::string findStudent(const std::string &);

    int deleteStudents(const std::unordered_multimap<std::string, std::string> &students, const User& user);

    std::string getPageStudents(const User& user);

    int editCourse(const std::unordered_multimap<std::string, std::string> &data, const User &user);

    int deleteCourse(int course_id);

    int createLesson(const std::unordered_multimap<std::string, std::string> &data, const User &user);

    int deleteLesson(const int lesson_id);

    std::string getPagePaymentsByStudent(const std::string &);

    std::pair<int, templates::Context> saveStudent(const std::unordered_multimap<std::string, std::string> &data, const User &user);
    //templates::Context verboseSearchStudent(const std::string &search, const User &user);
    templates::Template _render;

    templates::Context searchStudent(const std::string &search, const User& user);

    std::string getMainPage(const User & user) override;

    std::string schedule(const User &user);

    int editTeacher(const std::unordered_multimap<std::string, std::string> &data, const User &user);

    int editCabinet(const std::unordered_multimap<std::string, std::string> &data, const User &user);
private:
    //static templates::Context VerboseStudentSerializer(const VerboseStudent &student);
};

#endif //CORE_ADMINAPI_H
