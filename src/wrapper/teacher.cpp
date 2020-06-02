#include "teacher.h"
#include <utils.hpp>

std::vector<Course> Teacher::get_courses() const {
    SqlWrapper db;
    db << "select id, name, price, school_id from course where teacher_id=" << _id << ";";
    db.exec("Get courses by teacher");

    std::vector<Course> courses;
    courses.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        courses.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_int(2, i),
                db.get_int(3, i)
                );
    }
    db.disconnect();
    return courses;
}

Teacher Teacher::get_teacher(int teacher_id) {
    SqlWrapper db;
    db << "select name, surname, age, salary, tel_number, description, avatar from teacher "
       << "join users on teacher.user_id=users.id where teacher.id=" << teacher_id << ";";

    db.exec("Get teacher by id");
    db.disconnect();

    return Teacher(
            teacher_id,
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_int(4, 0),
            db.get_str(5, 0),
            db.get_str(6, 0),
            db.get_str(7, 0)
            );
}

int Teacher::save(const std::string& name, const std::string& surname, int salary,
                  int age, const std::string& tel_number, int user_id, const std::string& description) {
    SqlWrapper db;

    db << "insert into teacher(name, surname, age, salary, tel_number, user_id, description) "
       << "values ('" << name << "', '" << surname << "', " << age << ", " << salary << ", '" << tel_number
       << "', " << user_id << ", '" << description << "');";
    db.exec("Save teacher");

    db.disconnect();
    return 0;
}

int Teacher::remove(int teacher_id) {
    SqlWrapper db;

    db << "delete from teacher where id=" << teacher_id << ";";
    db.exec("Remove teacher");

    db.disconnect();
    return 0;
}

int Teacher::setMark(int lesson_id, int student_id, int mark, int school_id) const {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);
    auto today = converter.convert(boost::posix_time::second_clock::universal_time(), "");

    db << "insert into marks (student_id, teacher_id, school_id, mark, mark_date, lesson_id) "
       << "values (" << student_id << ", " << _id << ", " << school_id << ", " << mark << ", "
       << today << ", " << lesson_id << ";";
    db.exec("Set mark");

    db.disconnect();
    return 0;
}
