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
    Student give_me_a_name(teacher_id, t_name, t_surname, salary, description);
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
    if (!postgres.exec(query)) {
        throw std::exception();
    }
}

std::vector<Student> Course::get_student_list(const std::string& course_name) {

    std::string query = "SELECT id FROM course WHERE name='" + course_name + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int course_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);

    query = "SELECT * FROM student WHERE course_id=" + std::to_string(course_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Student> students;
    for (int i = 0; i < PQntuples(result); i++) {
        int s_id = atoi(PQgetvalue(result, i, 0));
        std::string s_name = std::string(PQgetvalue(result, i, 1));
        std::string s_surname = std::string(PQgetvalue(result, i, 2));
        int s_age = atoi(PQgetvalue(result, i, 3));
        std::string s_description = PQgetvalue(result, i, 4);
        auto res_student = Student(s_id, s_name, s_surname, s_age, s_description);
        students.push_back(res_student);
    }
    PQclear(result);
    return students;
}

