#include <iostream>
#include "sql_wrapper.h"
#include "course.h"
#include "teacher.h"
#include "student.h"

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

//    query = "INSERT INTO teacher VALUES(1, 'Olga', 'Smirnova', 12000, 'playing piano');";
//    postgres.exec(query);

//    pg_result* result = nullptr;
//    query = "SELECT teacher_id FROM course WHERE name='sambo';";
//    if (!postgres.query(query, result)) {
//        return 1;
//    }
    Course course(postgres);
    auto teacher = course.get_teacher("python programming");
    std::cout << teacher.return_surname() << std::endl;
    auto price = course.get_price("python programming");
    std::cout << price << std::endl;
    auto students = course.get_student_list("sambo");

    // Create Data storage object
//    using HandlerFunc = std::function<void (const ResultSet&)>;
//    const HandlerFunc handler;

//    if (postgres.is_select(query)) {
//        postgres.query(query/*, handler*/);
//    } else {
//        postgres.exec(query);
//    }

    std::cout << "It compiles" << std::endl;
    return 0;
}
