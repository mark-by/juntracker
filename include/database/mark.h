//
// Created by gg on 31.05.2020.
//

#ifndef JUNTRACKER_MARK_H
#define JUNTRACKER_MARK_H

#include "sql_wrapper.h"
#include "http/datetime.h"
#include "vector"

class Mark {
public:
    explicit Mark(int _id, int _student_id, int _teacher_id,
            int _school_id, int _mark, boost::posix_time::ptime _mark_date, int _lesson_id):
            _id(_id),
            _student_id(_student_id),
            _teacher_id(_teacher_id),
            _school_id(_school_id),
            _mark(_mark),
            _mark_date(_mark_date),
            _lesson_id(_lesson_id) { };

    static void save(int student_id, int course_id, int teacher_id,
            int school_id, int mark, boost::posix_time::ptime mark_date);
    static void update(int id, int student_id, int course_id, int teacher_id,
            int school_id, int mark, boost::posix_time::ptime mark_date);
    static void remove(int id);

private:
    int _id;
    int _student_id;
    int _teacher_id;
    int _school_id;
    int _mark;
    boost::posix_time::ptime _mark_date;
    int _lesson_id;
};

#endif //JUNTRACKER_MARK_H
