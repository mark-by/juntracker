#ifndef _VISIT_H_
#define _VISIT_H_

#include <string>

#include "sql_wrapper.h"

class Visit {
 public:
    Visit(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Visit(int id, int student_id, int course_id, std::string& visit_date)
            : id(id)
            , student_id(student_id)
            , course_id(course_id)
            , visit_date(visit_date) {}

    int get_student_id(int v_id) const;
    int get_course_id(int v_id) const;

 private: 
    int id;
    int student_id;
    int course_id;
    std::string visit_date;

    SqlWrapper postgres;
};

#endif  // _VISIT_H_