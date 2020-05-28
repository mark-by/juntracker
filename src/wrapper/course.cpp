#include "course.h"
#include <utils.hpp>

Teacher Course::get_teacher() const {
    auto postgres = connect();
    std::string query = "SELECT teacher_id FROM course WHERE name='" + name() + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    int teacher_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    query = "SELECT * FROM teacher WHERE id=" + std::to_string(teacher_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int salary = atoi(PQgetvalue(result, 0, 3));
    auto res_teacher = Teacher(teacher_id, t_name, t_surname, salary, postgres);
    PQclear(result);

    return res_teacher;
}

int Course::set_price(int price, int course_id) {
    auto postgres = connect();

    std::string query = "UPDATE course SET price=" + std::to_string(price)  + " WHERE id='" + std::to_string(course_id) + "';";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

std::vector<Student> Course::get_students() const {
    auto postgres = connect();
    std::string query = "SELECT id FROM course WHERE name='" + name() + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int course_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);

    query = "SELECT * FROM payment WHERE course_id=" + std::to_string(course_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Student> students;
    for (int i = 0; i < PQntuples(result); i++) {
        int s_id = atoi(PQgetvalue(result, i, 0));
        std::string s_name = std::string(PQgetvalue(result, i, 1));
        std::string s_surname = std::string(PQgetvalue(result, i, 2));
        int s_age = atoi(PQgetvalue(result, i, 3));
        auto res_student = Student(s_id, s_name, s_surname, s_age, postgres);
        students.push_back(res_student);
    }
    PQclear(result);
    return students;
}

Course Course::get_course(int course_id) {
    auto postgres = connect();

    std::string query = "SELECT * FROM course WHERE id=" + std::to_string(course_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string name = std::string(PQgetvalue(result, 0, 1));
    int price = atoi(PQgetvalue(result, 0, 2));
    auto res_course = Course(course_id, name, price);
    return res_course;
}

int Course::save(const std::string& name, int price) {
    auto postgres = connect();

    std::ostringstream s;
    std::string table_name = "course";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO course (id, name, price) VALUES ("
    << std::to_string(count_rows + 1) << ", '" << name << "', " << std::to_string(price) << ");";

    std::string query = s.str();

    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Course::remove(int course_id) {
    auto postgres = connect();

    std::string query = "DELETE FROM course WHERE id=" + std::to_string(course_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}
