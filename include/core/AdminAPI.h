#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

#include <string>
#include <unordered_map>
#include "API.h"
#include <template/template.h>

class AdminAPI : public API {
    struct StudentOnLesson {
        Student student;
        Lesson lesson;

        StudentOnLesson(const Student &student, const Lesson &lesson) : student(student), lesson(lesson) {}
    };

    struct WeekDay {
        std::string weekday;
        std::string date;
        std::vector<Lesson> lessons;
    };

public:
    AdminAPI() = default;

    std::string getMainPage(int userId) override;

    int saveCurrentLesson(const std::unordered_map<std::string, std::string> &);

    std::string findStudent(const std::string &);

    int deleteStudent(int student_id);

    int createStudent(const std::unordered_map<std::string, std::string> &);

    std::string getPageStudents(int);

    int addCourse(const std::string &);

    int deleteCourse(const std::string &);

    std::string getPagePaymentsByStudent(const std::string &);

private:
    static templates::Context CurrentLessonSerializer(const Lesson &lesson);

    static templates::Context StudentSerializer(const StudentOnLesson &student);

    static templates::Context ShortStudentSerializer(const Student &student);

    static templates::Context LessonSerializer(const Lesson &lesson);

    templates::Context DaySerializer(const WeekDay &weekday);

    templates::Template _render;
};

#endif //CORE_ADMINAPI_H
