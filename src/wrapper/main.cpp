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
#include <boost/filesystem.hpp>
#include <sstream>

int main(int argc, char* argv[]) {

    // Create Connection
    std::string filepath = "/config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    char ch;
    while (fin.get(ch)) {
        std::cout << ch;
        conninfo.push_back(ch);
    }
    fin.close();

    std::cout << boost::filesystem::current_path() << std::endl;
    std::cout <<  conninfo << std::endl;

    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    // Check Connection
    if (!postgres.is_connected()) {
        std::cout << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        return 1;
    }

    std::cout << "*** It compiles ***" << std::endl;
    return 0;
}
