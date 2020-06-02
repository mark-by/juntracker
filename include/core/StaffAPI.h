#ifndef JUNTRACKER_STAFFAPI_H
#define JUNTRACKER_STAFFAPI_H
#include <string>
#include <vector>
#include <student.h>
#include <lesson.h>
#include <context/context.h>
#include <API.h>
#include <user.h>

class StaffAPI: public API {
    struct WeekDay {
        std::string weekday;
        std::string date;
        std::vector<Lesson> lessons;

        WeekDay(const std::string &weekday, const std::string &date, const std::vector<Lesson>& lessons) :
                weekday(weekday), date(date), lessons(lessons) {}
    };
    struct StudentOnLesson {
        Student student;
        Lesson lesson;

        StudentOnLesson(const Student &student, const Lesson &lesson) : student(student), lesson(lesson) {}
    };
public:
    std::string getMainPage(const User & user) override;
    static templates::Context getUserData(const User &user);
    std::string schedule(const User &user);

protected:
    static templates::Context mainStaffData(const User & user);
    static templates::Context UserSerializer(const User &user);
    static templates::Context LessonSerializer(const Lesson &lesson);
    static templates::Context DaySerializer(const WeekDay &weekday);
    static templates::Context CurrentLessonSerializer(const Lesson &lesson);
    static templates::Context StudentSerializer(const StudentOnLesson &student);
    static templates::Context CourseSerializer(const Course &course);
    static templates::Context VerboseStudentSerializer(const VerboseStudent &student);
    static templates::Context mainScheduleStaffData(const User &user);
};

#endif //JUNTRACKER_STAFFAPI_H
