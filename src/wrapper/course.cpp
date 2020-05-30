#include "course.h"
#include <utils.hpp>

Teacher Course::get_teacher() const {
    SqlWrapper postgres;
    std::ostringstream query;
    query << "select teacher.id, teacher.name, age, surname, salary, tel_number, description, users.avatar "
          << "from teacher "
          << "join course on teacher.id=course.teacher_id"
          << "join users on users.id=teacher.user_id "
          << "where course.id=" << _id << ";";

    PGresult *result = nullptr;
    postgres.query(query.str(), &result, "Get teacher by course id");
    postgres.disconnect();

    return Teacher(
            std::stoi(PQgetvalue(result, 0, 0)),
            PQgetvalue(result, 0, 1),
            std::stoi(PQgetvalue(result, 0, 2)),
            PQgetvalue(result, 0, 3),
            std::stoi(PQgetvalue(result, 0, 4)),
            PQgetvalue(result, 0, 5),
            PQgetvalue(result, 0, 6),
            PQgetvalue(result, 0, 7)
            );
}

int Course::set_price(int price, int course_id) {
    SqlWrapper postgres;

    std::ostringstream query;
    query << "UPDATE course SET price=" << price << " WHERE id=" << course_id << ";";

    postgres.exec(query.str(), "Set price for course");
    postgres.disconnect();

    return 0;
}

std::vector<Student> Course::get_students() const {
    SqlWrapper postgres;
    PGresult *result = nullptr;

    std::ostringstream query;
    query << "select * from student s join students_for_course c on s.id=c.student_id where course_id=" << _id << ";";

    postgres.query(query.str(), &result, "Get students for course by id");

    std::vector<Student> students;
    for (int i = 0; i < PQntuples(result); i++) {
        students.emplace_back(
                std::stoi(PQgetvalue(result, i, 0)),
                PQgetvalue(result, i, 1),
                PQgetvalue(result, i, 2),
                std::stoi(PQgetvalue(result, i, 3)),
                PQgetvalue(result, i, 5)
        );
    }
    postgres.disconnect();

    return students;
}

Course Course::get_course(int course_id) {
    SqlWrapper postgres;

    std::ostringstream query;
    query << "SELECT * FROM course WHERE id=" << course_id << ";";

    PGresult *result = nullptr;
    postgres.query(query.str(), &result, "Get course by id");
    postgres.disconnect();

    return Course(
            std::stoi(PQgetvalue(result, 0, 0)),
            PQgetvalue(result, 0, 1),
            std::stoi(PQgetvalue(result, 0, 2)),
            std::stoi(PQgetvalue(result, 0, 3)),
            std::stoi(PQgetvalue(result, 0, 4))
    );

}

int Course::save(const std::string& name, int price, int schoolId, int teacher_id) {
    SqlWrapper postgres;

    std::ostringstream s;
    s << "INSERT INTO course(name, price, teacher_id, school_id) VALUES ('"
      << name << "', " << price << ", " << teacher_id << ", " << schoolId << ");";

    postgres.exec(s.str(), "Save course");
    postgres.disconnect();

    return 0;
}

int Course::remove(int course_id) {
    SqlWrapper postgres;

    std::ostringstream query;
    query << "DELETE FROM course WHERE id=" << course_id << ";";

    postgres.exec(query.str(), "Remove course");
    postgres.disconnect();

    return 0;
}
