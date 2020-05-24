#ifndef _VISIT_H_
#define _VISIT_H_

#include <string>
#include <sstream>

#include "sql_wrapper.h"

class Visit {
 public:
    Visit(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Visit(int _id, int _student_id, int _course_id, int _lesson_id)
            : _id(_id)
            , _student_id(_student_id)
            , _course_id(_course_id)
            , _lesson_id(_lesson_id) {}

    int get_student_id(int v_id) const;
    int get_course_id(int v_id) const;

    Visit get_visit(int v_id) const;
    int add_visit(const Visit& visit) const;
    int delete_visit(int v_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] int student_id() const { return _student_id; }
    [[nodiscard]] int course_id() const { return _course_id; }
    [[nodiscard]] int lesson_id() const { return _lesson_id; }

 private: 
    int _id;
    int _student_id;
    int _course_id;
    int _lesson_id;

    SqlWrapper postgres;
};

#endif  // _VISIT_H_