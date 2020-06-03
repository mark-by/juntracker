#include "student.h"
#include <utils.hpp>
#include <vector>


std::vector<Course> Student::get_courses() const {
    SqlWrapper db;
    db << "select course.id, name, price, school_id "
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
                db.get_int(3, i)
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

int Student::save(const std::string name, const std::string &surname, int age,
        const std::string &description, const std::string &tel_number, const std::string& email,
                  const std::string &parent_name, const std::string& avatar, int school_id) {
    SqlWrapper db;

    std::string login;
    do {
        login = randomStr(10);
        db << "select * from users where login='" << login << "';";
    } while (db.count_tupls() > 0);
    std::string password = randomStr(12);

    db << "insert into users (email, login, password, permission, avatar, school_id) values ('" << email << "', '"
       << login << "', '" << password << "', " << 0 << ", '"
       << avatar << "', " << school_id << ") returning id;";
    db.exec("Create student from save");

    int user_id = db.get_int(0);
    db << "insert into student (name, surname, age, user_id, description, tel_number, parent_name) "
       << "values('" << name << "', '" << surname << "', " << age << ", " << user_id
       << ", '" << description << "', '" << tel_number << "', '" << parent_name << "') returning id;";
    db.exec("Save student");

    db.disconnect();
    return db.get_int(0);
}

int Student::remove(int student_id) {
    SqlWrapper db;

    db << "delete from student where id=" << student_id << ";";
    db.exec("Remove student");
    db.disconnect();

    return 0;
}

std::vector<Student> Student::get_students_like(const std::string &str, int school_id) {
    SqlWrapper db;
    std::pair<std::string, std::string> name_surname = parse_name_surname(str);
    std::vector<Student> res_students;
    if (name_surname.first.empty() && name_surname.second.empty()) {
        return res_students;
    }

    if (name_surname.second.empty()) {
        db << "select * from student s join users u on s.user_id=u.id where name like '" << name_surname.first
           << "%' or surname like '" << name_surname.first << "%' and school_id=" << school_id << ";";
    } else {
        db << "select * from student s join users u on s.user_id=u.id where name like '" << name_surname.first
           << "%' and surname like '" << name_surname.second << "%' and school_id=" << school_id << " union "
           << "select * from student s join users u on s.user_id=u.id where name like '" << name_surname.second
           << "%' and surname like '" << name_surname.first << "%' and school_id=" << school_id << ";";
    }

    db.exec("Find students like");

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

std::vector<Mark> Student::get_marks_by_course(int course_id) const {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);

    db << "select * from marks where student_id=" << _id << " and course_id=" << course_id << ";";
    db.exec("Find students like");

    std::vector<Mark> marks;
    marks.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        marks.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i),
                converter.convert(db.get_str(5, i)),
                db.get_int(6, i)
        );
    }

    db.disconnect();
    return marks;
}

std::string Student::avatar() const {
    SqlWrapper db;

    db << "select avatar from student s join user u on s.user_id=u.id where id=" << _id << ";";
    db.exec("getting student avatar");

    db.disconnect();
    std::string res = db.get_str(0, 0);

    return res;
}

std::vector<Visit> Student::get_visits() {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);

    db << "select * from visit where student_id=" << _id << ";";
    db.exec("Find students visits");

    std::vector<Visit> visits;
    visits.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        visits.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_bool(3, i),
                converter.convert(db.get_str(4, i)),
                db.get_int(5, i)
                );
    }

    db.disconnect();
    return visits;
}
