//
// Created by gg on 31.05.2020.
//

#include "mark.h"

void Mark::save(int student_id, int course_id, int teacher_id, int school_id, int mark, boost::posix_time::ptime mark_date) {
    SqlWrapper db;
    std::string date = DateTimeConverter.convert(mark_date);

    db << "insert into mark (student_id, course_id, teacher_id, school_id, mark, mark_date) values("
       << student_id << ", " << course_id << ", " << teacher_id << ", '"
       << school_id << "', " << mark << "', '" << date << "');";
    db.exec("Save mark");

    db.disconnect();
}

void Mark::update(int id, int student_id, int course_id, int teacher_id, int school_id, int mark, boost::posix_time::ptime mark_date) {
    SqlWrapper db;
    std::string date = DateTimeConverter.convert(mark_date);

    db << "update mark set"
        << " student_id=" << student_id
        << ", course_id=" << course_id
        << ", teacher_id=" << teacher_id
        << ", school_id=" << school_id
        << ", mark=" << mark
        << ", mark_date='" << date
        << "', where id=" << id << ";";
    db.exec("Update mark by id");

    db.disconnect();
}

void Mark::remove(int id) {
    SqlWrapper db;

    db << "delete from mark where id=" << id << ";";
    db.exec("Delete mark by id");

    db.disconnect();
}
