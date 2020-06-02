#include "course.h"
#include <utils.hpp>


int Course::set_price(int price, int course_id) {
    SqlWrapper db;

    db << "UPDATE course SET price=" << price << " WHERE id=" << course_id << ";";
    db.exec("Set price for course");

    db.disconnect();
    return 0;
}

std::vector<Student> Course::get_students() const {
    SqlWrapper db;

    db << "select * from student s join students_for_course c on s.id=c.student_id where course_id=" << _id << ";";
    db.exec("Get students for course by id");

    std::vector<Student> students;
    students.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        students.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_str(2, i),
                db.get_int(3, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_str(7, i)
        );
    }
    db.disconnect();

    return students;
}

Course Course::get_course(int course_id) {
    SqlWrapper db;

    db << "SELECT * FROM course WHERE id=" << course_id << ";";
    db.exec("Get course by id");

    db.disconnect();
    return Course(
            db.get_int(0),
            db.get_str(1),
            db.get_int(2),
            db.get_int(3)
    );

}

int Course::save(const std::string &name, int price, int schoolId) {
    SqlWrapper db;

    db << "INSERT INTO course(name, price, school_id) VALUES ('"
       << name << "', " << price << ", " << schoolId << ");";
    db.exec("Save course");

    db.disconnect();
    return 0;
}

int Course::remove(int course_id) {
    SqlWrapper db;

    db << "DELETE FROM course WHERE id=" << course_id << ";";
    db.exec("Remove course");

    db.disconnect();
    return 0;
}

int Course::update(int course_id, const std::string &name, int price, int schoolId) {
    SqlWrapper db;

    db << "update course set "
       << "name='" << name << "', "
       << "price=" << price << "', "
       << "school_id=" << schoolId
       << "where course_id=" << course_id << ";";
    db.exec("Update course");

    db.disconnect();
    return 0;
}
