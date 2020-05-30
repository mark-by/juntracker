#include "lesson.h"
#include "utils.hpp"

std::vector<Student> Lesson::get_students() const {
    SqlWrapper db;

    db << "select * from student "
       << "join students_for_lesson s on s.student_id=student.id "
       << "where s.lesson_id=" << _id << ";";
    db.exec("Students on lesson");

    std::vector<Student> res_students;
    res_students.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_students.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_str(2, i),
                db.get_int(3, i),
                db.get_str(4, i),
                db.get_str(5, i),
                db.get_str(6, i)
                );
    }

    db.disconnect();
    return res_students;
}

Teacher Lesson::get_teacher() const {
    SqlWrapper db;

    db << "select teacher.id, teacher.name, teacher.surname, teacher.age, teacher.salary, "
       << "teacher.tel_number, teacher.description, avatar from teacher "
       << "join users on teacher.user_id=users.id "
       << "join lesson on lesson.teacher_id=teacher.id "
       << "where lesson.id=" << _id << ";";
    db.exec("Get teacher for lesson");

    db.disconnect();
    return Teacher(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_int(4, 0),
            db.get_str(5, 0),
            db.get_str(6, 0),
            db.get_str(7, 0)
            );
}

Course Lesson::get_course() const {
    SqlWrapper db;

    db << "select * from course join lesson on lesson.course_id=course.id where lesson.id=" << _id << ";";
    db.exec("Get lesson title");

    db.disconnect();
    return Course(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_int(2, 0),
            db.get_int(3, 0),
            db.get_int(4, 0)
    );
}

Lesson Lesson::get_lesson(int lesson_id) {
    SqlWrapper db;

    db << "select * from lesson where id=" << lesson_id << ";";
    db.exec("Get lesson");

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

int Lesson::save(int course_id, int cabinet_id, int teacher_id, int weekday,
        const std::string& start_time, const std::string& end_time, int school_id) {
    SqlWrapper db;

    db << "insert into lesson (course_id, cabinet_id, teacher_id, weekday, start_time, end_time, school_id) "
       << "values (" << course_id << ", " << cabinet_id << ", " << teacher_id << ", " << weekday << ", '"
       << start_time << "', '" << end_time << "', " << school_id << ";";
    db.exec("Save lesson");

    db.disconnect();
    return 0;
}

int Lesson::remove(int lesson_id) {
    SqlWrapper db;

    db << "delete from lesson where id=" << lesson_id << ";";
    db.exec("Remove lesson");

    db.disconnect();
    return 0;
}

Cabinet Lesson::get_cabinet() const {
    SqlWrapper db;

    db << "select * from cabinet join lesson on lesson.cabinet_id=cabinet.id where lesson.id=" << _id << ";";
    db.exec("Get cabinet from lesson");

    db.disconnect();
    return Cabinet(
            db.get_int(0),
            db.get_str(1),
            db.get_int(2)
            );
}



