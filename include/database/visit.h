#ifndef _VISIT_H_
#define _VISIT_H_

#include <string>

class Visit {
 public:
    explicit Visit();

    int get_student_id() const;
    int get_course_id() const;

 private: 
    int id;
    int student_id;
    int course_id;
    std::string visit_date;
};

#endif  // _VISIT_H_