#include <iostream>
#include <fstream>

#include "course.h"
#include "lesson.h"
#include "payment.h"
#include "payment_history.h"
#include "sql_wrapper.h"
#include "student.h"
#include "teacher.h"
#include "user.h"
#include "visit.h"
#include "visit_history.h"

int main(int argc, char* argv[]) {

    // Create Connection
    std::string filepath = "/home/andrey/juntracker/config/config.txt";
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
    Teacher teacher = course.get_teacher("python programming");
    std::cout << teacher.return_surname() << std::endl;
    auto price = course.get_price("python programming");
    std::cout << price << std::endl;
    auto students = course.get_student_list("sambo");
//    Teacher t(postgres);
//    std::cout << course.get_courses_by_teacher(1)<< std::endl;
    Student s(postgres);
    std::cout << s.get_surname(8) << " " << s.get_course(8)<< std::endl;
    User u(postgres);
    std::cout << u.get_status(11) << std::endl;
    Visit v(postgres);
    std::cout << v.get_course_id(11) << std::endl;
    Payment p(postgres);
    std::cout << p.get_course_id(11) << std::endl;
    PaymentHistory ph(postgres);
    auto payments = ph.get_payments_by_course(1);
    for (const auto&  pay : payments) {
        std::cout << pay.return_amount() << " ";
    }
    std::cout << std::endl;
    VisitHistory vh(postgres);
    auto visits = vh.get_visits_by_course(2);
    for (const auto&  visit : visits) {
        std::cout << visit.return_course_id() << " ";
    }
    std::cout << std::endl;
//    Lesson l(postgres);

    std::cout << "*** It compiles ***" << std::endl;
    return 0;
}
