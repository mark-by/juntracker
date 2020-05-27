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
#include "utils.hpp"

int main(int argc, char* argv[]) {

    auto postgres = connect();

    // Check Connection
    if (!postgres.is_connected()) {
        std::cout << "Connection to database failed: " << PQerrorMessage(postgres.getConn()) << std::endl;
        return 1;
    }

    std::cout << "*** It compiles ***" << std::endl;
    return 0;
}
