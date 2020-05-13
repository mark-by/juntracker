#include "teacher.h"

std::string Teacher::get_name(int t_id) const {
    std::string query = "SELECT name FROM teacher WHERE id='" + std::to_string(t_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = PQgetvalue(result, 0, 0);
    PQclear(result);
    return t_name;
}

std::string Teacher::get_surname(int t_id) const {
    std::string query = "SELECT surname FROM teacher WHERE id='" + std::to_string(t_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_surname = PQgetvalue(result, 0, 0);
    PQclear(result);
    return t_surname;
}

std::string Teacher::get_course(int t_id) const {
    std::string query = "SELECT teacher_id FROM course WHERE id='" + std::to_string(t_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string c_id = PQgetvalue(result, 0, 0);
    query = "SELECT description FROM teacher WHERE id=" + c_id + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string c_name = PQgetvalue(result, 0, 0);
    return c_name;
}

Teacher Teacher::get_teacher(int t_id) const {
    std::string query = "SELECT * FROM teacher WHERE id=" + std::to_string(t_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int t_salary = atoi(PQgetvalue(result, 0, 3));
    std::string t_description = PQgetvalue(result, 0, 4);
    auto res_teacher = Teacher(t_id, t_name, t_surname, t_salary, t_description);
    return res_teacher;
}

int Teacher::add_teacher(const Teacher& teacher) const {
    std::ostringstream s;
    s << "INSERT INTO teacher VALUES (" << std::to_string(teacher.id) << ", "
      << teacher.name << ", " << teacher.surname << ", "
      << std::to_string(teacher.salary) << teacher.description <<");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Teacher::delete_teacher(int t_id) const {
    std::string query = "DELETE * FROM teacher WHERE id=" + std::to_string(t_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}