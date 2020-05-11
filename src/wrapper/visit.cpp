#include "visit.h"

int Visit::get_student_id(int v_id) const {
    std::string query = "SELECT student_id FROM visit WHERE id='" + std::to_string(v_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int s_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return s_id;
}

int Visit::get_course_id(int v_id) const {
    std::string query = "SELECT course_id FROM visit WHERE id='" + std::to_string(v_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int c_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return c_id;
}

