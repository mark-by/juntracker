#ifndef _VISIT_H_
#define _VISIT_H_

#include <string>
#include <sstream>

#include "sql_wrapper.h"

class Visit {
 public:
    Visit(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Visit(int id, int student_id, int course_id, int lesson_id)
            : id(id)
            , student_id(student_id)
            , course_id(course_id)
            , lesson_id(lesson_id) {}

    int get_student_id(int v_id) const;
    int get_course_id(int v_id) const;
    int return_course_id() const { return course_id; }

    Visit get_visit(int v_id) const;
    int add_visit(const Visit& visit) const;
    int delete_visit(int v_id) const;

 private: 
    int id;
    int student_id;
    int course_id;
    int lesson_id;

    SqlWrapper postgres;
};

#endif  // _VISIT_H_