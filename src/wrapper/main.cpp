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
    SqlWrapper postgres;

    auto lesson = Lesson::get_lesson(4);
    std::cout << lesson.start_time() << " " << lesson.end_time() << std::endl;

    std::cout << "*** It compiles ***" << std::endl;
    postgres.disconnect();
    return 0;
}
