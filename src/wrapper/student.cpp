#include "student.h"
#include <utils.hpp>
#include <vector>


std::vector<Course> Student::get_courses() const {
    SqlWrapper db;
    db << "select course.id, name, price, teacher_id, school_id "
       << "from course "
       << "join students_for_course c on course.id=c.course_id "
       << "where c.student_id=" << _id << ";";
    db.exec("Get courses by student");

    std::vector<Course> courses;
    courses.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        courses.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i)
        );
    }

    db.disconnect();

    return courses;
}

Visit Student::get_visit(int lesson_id, const boost::posix_time::ptime &date) const {
    SqlWrapper db;

    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);

    db << "SELECT * FROM visit WHERE lesson_id=" << std::to_string(lesson_id) << " and visit_date='"
    << converter.convert(boost::posix_time::second_clock::universal_time(), "") << "' and student_id=" << _id << ";";

    db.exec("Get visit by student");
    db.disconnect();

    return Visit(
            db.get_int(0, 0),
            db.get_int(1, 0),
            db.get_int(2, 0),
            db.get_bool(3, 0),
            converter.convert(db.get_str(4)),
            db.get_int(5, 0)
            );
}

Student Student::get_student(int student_id) {
    SqlWrapper db;

    db << "select id, name, surname, age, description, tel_number, parent_name"
          << " from student where id=" << student_id << ";";
    db.exec("Get student by id");
    db.disconnect();

    return Student(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_str(4, 0),
            db.get_str(5, 0),
            db.get_str(6, 0)
            );
}

int Student::save(const std::string name, const std::string& surname, int age,
        int user_id, const std::string& description, const std::string& tel_number, const std::string& parent_name) {
    SqlWrapper db;

    db << "insert into student (name, surname, age, user_id, description, tel_number, parent_name) "
       << "values('" << name << "', '" << surname << "', " << age << ", " << user_id
       << ", '" << description << ", '" << tel_number << ", '" << parent_name << "');";
    db.exec("Save student");
    db.disconnect();

    return 0;
}

int Student::remove(int student_id) {
    SqlWrapper db;

    db << "delete from student where id=" << student_id << ";";
    db.exec("Remove student");
    db.disconnect();

    return 0;
}

std::vector<Student> Student::get_students_like(const std::string &str) {
    SqlWrapper db;
    std::pair<std::string, std::string> name_surname = parse_name_surname(str);

    if (name_surname.second.empty()) {
        db << "select * from student where name like '" << name_surname.first
            << "' or surname like '" << name_surname.first << "';";
    } else {
        db << "select * from student where name like '" << name_surname.first
           << "' or surname like '" << name_surname.second << "' union "
           << "select * from student where name like '" << name_surname.second
           << "' or surname like '" << name_surname.first << "';";
    }

    db.exec("Find students like");

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


