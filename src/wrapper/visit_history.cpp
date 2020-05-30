#include "visit_history.h"

std::vector<Visit> VisitHistory::get_visits_by_student(int s_id) const {
    SqlWrapper db;
    const std::string format = "%d.%m.%Y";
    DateTimeConverter converter(format);

    db << "select id, student_id, lesson_id, was_in_class, visit_date, school_id from visit "
       << "where student_id=" << s_id << ";";
    db.query("Get student visits");

    std::vector<Visit> res_visits;
    res_visits.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_visits.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_bool(3, i),
                converter.convert(db.get_str(4, i)),
                db.get_int(5, i)
                );
    }

    db.disconnect();
    return res_visits;
}

std::vector<Visit> VisitHistory::get_visits_by_lesson(int c_id) const {
    SqlWrapper db;
    const std::string format = "%d.%m.%Y";
    DateTimeConverter converter(format);

    db << "select id, student_id, lesson_id, was_in_class, visit_date, school_id from visit "
       << "where lesson_id=" << c_id << " and was_in_class=true;";
    db.query("Get visits on lesson");


    std::vector<Visit> res_visits;
    res_visits.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_visits.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_bool(3, i),
                converter.convert(db.get_str(4, i)),
                db.get_int(5, i)
        );
    }
    db.disconnect();

    return res_visits;
}

