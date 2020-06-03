#include "visit.h"
#include <utils.hpp>

Student Visit::get_student() const {
    SqlWrapper db;

    db << "SELECT student.id, student.name, student.surname, student.age, student.description FROM student "
       << "join visit on visit.student_id=student.id where visit.id" << _id << ";";
    db.exec("Get student by visit id");
    db.disconnect();

    return Student(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_str(4, 0),
            db.get_str(5, 0),
            db.get_str(6, 0)
    );
}

Lesson Visit::get_lesson() const {
    SqlWrapper db;

    db << "SELECT lesson.id, lesson.course_id, lesson.cabinet_id, lesson.teacher_id, "
       << "lesson.weekday, lesson.start_time, lesson.end_time, lesson.school_id FROM lesson "
       << "join visit on visit.lesson_id=lesson.id where visit.id=" << _id << ";";
    db.exec("Get student by visit id");
    db.disconnect();

    return Lesson(
            db.get_int(0, 0),
            db.get_int(1, 0),
            db.get_int(2, 0),
            db.get_int(3, 0),
            db.get_int(4, 0),
            db.get_str(5, 0),
            db.get_str(6, 0),
            db.get_int(7, 0)
    );
}

Visit Visit::get_visit(int visit_id) {
    SqlWrapper db;

    db << "select id, student_id, lesson_id, was_in_class, visit_date, school_id from visit where id="
       << visit_id << ";";
    db.exec("Get visit");

    db.disconnect();
    return Visit(
            db.get_int(0, 0),
            db.get_int(1, 0),
            db.get_int(2, 0),
            db.get_bool(3, 0),
            db.get_str(4, 0),
            db.get_int(5, 0)
            );
}

int Visit::save(int student_id, int lesson_id, bool was_in_class) {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);
    auto today = converter.convert(boost::posix_time::second_clock::universal_time(), "");

    char was_in_class_ch = (was_in_class ? 't' : 'f');

    db << "select count(*) from visit "
       << "where student_id=" << student_id << " and lesson_id=" << lesson_id <<
    " and visit_date='" << today << "';";
    db.exec("Count visit");
    int count = db.get_int(0, 0);

    db << "select school_id from lesson where id=" << lesson_id << ";";
    db.exec("School id");
    int school_id = db.get_int(0);

    if (count) {
        db << "update visit set was_in_class='"
           << was_in_class_ch << "' where student_id=" << student_id <<
        " and lesson_id=" << lesson_id << " and visit_date='" << today << "' and school_id=" << school_id << ";";
    } else {
        db << "insert into visit (student_id, lesson_id, was_in_class, visit_date, school_id) "
           << "values (" << student_id << ", " << lesson_id << ", '" << was_in_class << "', '"
           << today << "', " << school_id << ");";
    }

    db.exec("Save visit");
    db.disconnect();

    return 0;
}

int Visit::remove(int visit_id) {
    SqlWrapper db;

    db << "delete from visit where id=" << visit_id << ";";
    db.exec("Remove visit");

    db.disconnect();
    return 0;
}

