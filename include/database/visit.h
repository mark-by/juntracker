#ifndef INCLUDE_DATABASE_VISIT_H_
#define INCLUDE_DATABASE_VISIT_H_

#include "sql_wrapper.h"
class Visit;
#include "student.h"
class Lesson;
#include "lesson.h"

class Visit {
 public:
    Visit(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Visit(int _id, bool _was_in_class, SqlWrapper postgres)
            : _id(_id)
            , _was_in_class(_was_in_class)
            , postgres(postgres) {}

    Student get_student() const;
    Lesson get_lesson() const;

    static Visit get_visit(int visit_id);
    static int save(int student_id, int lesson_id, bool was_in_class);
    static int remove(int visit_id);

    int id() const { return _id; }
    bool was_in_class() const { return _was_in_class; }

 private: 
    int _id;
    bool _was_in_class;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_VISIT_H_