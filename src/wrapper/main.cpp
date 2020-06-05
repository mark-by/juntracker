#include <iostream>
#include <fstream>
#include "course.h"
#include "lesson.h"
#include "sql_wrapper.h"

int main(int argc, char* argv[]) {
    SqlWrapper postgres;

    auto lesson = Lesson::get_lesson(4);
    std::cout << lesson.start_time() << " " << lesson.end_time() << std::endl;

    std::cout << "*** It compiles ***" << std::endl;
    postgres.disconnect();
    return 0;
}
