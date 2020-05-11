#include <iostream>

#include "sql_wrapper.h"
#include "course.h"
#include "teacher.h"
#include "student.h"
#include "user.h"
#include "visit.h"

int main(int argc, char* argv[]) {

    std::string query;

    // Create Connection
    const char* conninfo = "host=localhost port=5432 dbname=jun_tracker user=amavrin password=root";
    PGconn *conn = PQconnectdb(conninfo);

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
    Teacher t(postgres);
    std::cout << t.get_course(1)<< std::endl;
    Student s(postgres);
    std::cout << s.get_surname(8) << " " << s.get_course(8)<< std::endl;
    User u(postgres);
    std::cout << u.get_status(11) << std::endl;
//    Visit v(postgres);
//    std::cout << v.get_course_id(11) << std::endl;

//    if (postgres.is_select(query)) {
//        postgres.query(query/*, handler*/);
//    } else {
//        postgres.exec(query);
//    }

    std::cout << "*** It compiles ***" << std::endl;
    return 0;
}
