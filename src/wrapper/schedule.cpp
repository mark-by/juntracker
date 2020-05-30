#include "schedule.h"

std::vector<Lesson> Schedule::get_schedule_by_student(int s_id) const {
    SqlWrapper db;

    db << "select * from lesson "
       << "join payment on lesson.course_id=payment.course_id where payment.student_id=" << s_id << ";";
    db.exec("Get schedule by student");

    std::vector<Lesson> schedule;
    schedule.reserve(db.count_tupls());

    for (int i = 0; i < db.count_tupls(); i++) {
        schedule.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_int(7, i)
        );
    }

    db.disconnect();
    return schedule;
}

std::vector<Lesson> Schedule::get_schedule_by_course(int c_id) const {
    SqlWrapper db;

    db << "select * from lesson where course_id=" << c_id << ";";
    db.exec("Get schedule by course");

    std::vector<Lesson> schedule;
    schedule.reserve(db.count_tupls());

    for (int i = 0; i < db.count_tupls(); i++) {
        schedule.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_int(7, i)
        );
    }

    db.disconnect();
    return schedule;
}

std::vector<Lesson> Schedule::get_schedule_by_teacher(int t_id) const {
    SqlWrapper db;

    db << "select * from lesson where teacher_id=" << t_id << ";";
    db.exec("Get schedule by teacher");

    std::vector<Lesson> schedule;
    schedule.reserve(db.count_tupls());

    for (int i = 0; i < db.count_tupls(); i++) {
        schedule.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_int(7, i)
        );
    }

    db.disconnect();
    return schedule;
}
