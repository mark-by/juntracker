#include <iostream>
#include <fstream>

#include "course.h"
#include "lesson.h"
#include "payment.h"
#include "payment_history.h"
#include "schedule.h"
#include "session.h"
#include "sql_wrapper.h"
#include "student.h"
#include "teacher.h"
#include "user.h"
#include "visit.h"
#include "visit_history.h"

int main(int argc, char* argv[]) {

    // Create Connection
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();

    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    // Check Connection
    if (!postgres.is_connected()) {
        std::cout << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        return 1;
    }

    Course course(postgres);
//    Teacher teacher = course.get_teacher("python programming");
//    std::cout << teacher.surname() << std::endl;
//    std::cout << teacher.name() << std::endl;
//    teacher.get_courses();
//    std::string stud_name = "Egor";
//    std::string stud_surname = "Zvonarev";
//    Student stud = Student(9, stud_name, stud_surname, 12);
//    stud.get_courses();
//    Teacher t(postgres);
//    std::cout << t.get_name(1) << std::endl;
//    auto students = course.get_students();
//    Student s(postgres);
//    std::cout << s.get_surname(8) << std::endl;
    User u(postgres);
    u.get_current_lessons();
    Visit v(postgres);
    std::cout << v.get_lesson_id(7) << std::endl;
//    Payment p(postgres);
//    std::cout << p.get_course_id(8) << std::endl;
    PaymentHistory ph(postgres);
    auto payments = ph.get_payments_by_course(1);
    for (const auto&  pay : payments) {
        std::cout << pay.amount() << " ";
    }
    std::cout << std::endl;
    VisitHistory vh(postgres);
    auto visits = vh.get_visits_by_lesson(2);
    for (const auto&  visit : visits) {
        std::cout << visit.student_id() << " ";
    }
    std::cout << std::endl;
    Lesson l(postgres);
//    l.get_students(5);
//    std::cout << l.get_weekday(3) << " " << l.get_start(3) << " " << l.get_end(3) << std::endl;
    Schedule sh(postgres);
    sh.get_schedule_by_student(1);
    sh.get_schedule_by_course(3);
    sh.get_schedule_by_teacher(4);
    std::string l_weekday = "thirsday";
    std::string l_start = "17:30";
    std::string l_end = "19:00";
    Lesson ins_lesson = Lesson(10,  5,  l_weekday, l_start, l_end);

    std::cout << "*** It compiles ***" << std::endl;
    return 0;
}
