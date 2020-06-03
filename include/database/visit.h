#ifndef INCLUDE_DATABASE_VISIT_H_
#define INCLUDE_DATABASE_VISIT_H_

#include "sql_wrapper.h"

class Visit;

#include "student.h"

class Lesson;

#include "lesson.h"
#include "http/datetime.h"
#include "utils.hpp"

class Visit {
public:
    explicit Visit(int _id, int _student_id, int _lesson_id, bool _was_in_class,
            const std::string &_visit_date, int _school_id):
            _id(_id),
            _student_id(_student_id),
            _lesson_id(_lesson_id),
            _was_in_class(_was_in_class),
            _visit_date(_visit_date),
            _school_id(_school_id) {}

    Student get_student() const;
    Lesson get_lesson() const;

    static Visit get_visit(int visit_id);
    static int save(int student_id, int lesson_id, bool was_in_class);
    static int remove(int visit_id);

    int id() const { return _id; }
    bool was_in_class() const { return _was_in_class; }
    std::string date() const { return _visit_date; }

private:
    int _id;
    int _student_id;
    int _lesson_id;
    bool _was_in_class;
    std::string _visit_date;
    int _school_id;

};

#endif  // INCLUDE_DATABASE_VISIT_H_