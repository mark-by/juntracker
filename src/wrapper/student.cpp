#include "student.h"

std::string Student::get_name(int s_id) const {
    std::string query = "SELECT name FROM student WHERE id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = PQgetvalue(result, 0, 0);
    PQclear(result);
    return t_name;
}

std::string Student::get_surname(int s_id) const {
    std::string query = "SELECT surname FROM student WHERE id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_surname = PQgetvalue(result, 0, 0);
    PQclear(result);
    return t_surname;
}

