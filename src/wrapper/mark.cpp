//
// Created by gg on 31.05.2020.
//

#include "mark.h"

void Mark::save(int student_id, int lesson_id, int teacher_id, int school_id, int mark, boost::posix_time::ptime mark_date) {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);
    std::string date = converter.convert(mark_date);

    db << "insert into mark (student_id, lesson_id, teacher_id, school_id, mark, mark_date) values("
       << student_id << ", " << lesson_id << ", " << teacher_id << ", '"
       << school_id << "', " << mark << "', '" << date << "');";
    db.exec("Save mark");

    db.disconnect();
}

void Mark::update(int id, int student_id, int lesson_id, int teacher_id, int school_id, int mark, boost::posix_time::ptime mark_date) {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);
    std::string date = converter.convert(mark_date);

    db << "update mark set"
        << " student_id=" << student_id
        << ", lesson_id=" << lesson_id
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
