#include "course.h"
#include <utils.hpp>

Teacher Course::get_teacher() const {
    SqlWrapper postgres;
    std::string query = "SELECT teacher_id FROM course WHERE name='" + name() + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }

    int teacher_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM teacher WHERE id=" + std::to_string(teacher_id) + ";";
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int salary = atoi(PQgetvalue(result, 0, 3));
    postgres.disconnect();
    return Teacher(teacher_id, t_name, t_surname, salary);
}

int Course::set_price(int price, int course_id) {
    SqlWrapper postgres;

    std::string query = "UPDATE course SET price=" + std::to_string(price)  + " WHERE id='" + std::to_string(course_id) + "';";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

std::vector<Student> Course::get_students() const {
    SqlWrapper postgres;
    PGresult *result = nullptr;

    std::string query = "select * from student s join students_for_course c on s.id=c.student_id where course_id="
            + std::to_string(_id) + ";";

    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }

    std::vector<Student> students;
    for (int i = 0; i < PQntuples(result); i++) {
        int s_id = atoi(PQgetvalue(result, i, 0));
        std::string s_name = std::string(PQgetvalue(result, i, 1));
        std::string s_surname = std::string(PQgetvalue(result, i, 2));
        int s_age = atoi(PQgetvalue(result, i, 3));
        auto res_student = Student(s_id, s_name, s_surname, s_age);
        students.push_back(res_student);
    }

    postgres.disconnect();
    return students;
}

Course Course::get_course(int course_id) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM course WHERE id=" + std::to_string(course_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string name = std::string(PQgetvalue(result, 0, 1));
    int price = atoi(PQgetvalue(result, 0, 2));
    postgres.disconnect();
    return Course(course_id, name, price);
}

int Course::save(const std::string& name, int price) {
    SqlWrapper postgres;

    std::ostringstream s;
    std::string table_name = "course";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO course (id, name, price) VALUES ("
    << std::to_string(count_rows + 1) << ", '" << name << "', " << std::to_string(price) << ");";

    std::string query = s.str();

    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int Course::remove(int course_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM course WHERE id=" + std::to_string(course_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}
