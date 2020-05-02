#include "course.h"

Teacher Course::get_teacher(const std::string& course_name) const {
    std::string query = "SELECT teacher_id FROM course WHERE name='" + course_name + "';";
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
    std::string description = PQgetvalue(result, 0, 4);
    auto res_teacher = Teacher(teacher_id, t_name, t_surname, salary, description);
    PQclear(result);

    return res_teacher;
}

int Course::get_price(const std::string& course_name) const {
    std::string query = "SELECT price FROM course WHERE name='" + course_name + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int c_price = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return c_price;
}

void Course::set_price(int price, const std::string& course_name) {
    std::string query = "UPDATE course SET price=" + std::to_string(price)  + " WHERE name='" + course_name + "';";
    std::cout << query << std::endl;
    if (!postgres.exec(query)) {
        throw std::exception();
    }
}

