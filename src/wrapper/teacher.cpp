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