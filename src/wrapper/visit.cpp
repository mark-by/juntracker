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

int Visit::get_lesson_id(int v_id) const {
    std::string query = "SELECT lesson_id FROM visit WHERE id='" + std::to_string(v_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int c_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return c_id;
}

Visit Visit::get_visit(int v_id) const {
    std::string query = "SELECT * FROM visit WHERE id=" + std::to_string(v_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int v_student_id = atoi(PQgetvalue(result, 0, 1));
    int v_course_id = atoi(PQgetvalue(result, 0, 2));
    int v_lesson_id = atoi(PQgetvalue(result, 0, 3));
    auto res_visit = Visit(v_id, v_student_id, v_course_id, v_lesson_id);
    return res_visit;
}

int Visit::add_visit(const Visit& visit) const {
    std::ostringstream s;
    s << "INSERT INTO visit VALUES (" << std::to_string(visit.id()) << ", "
      << std::to_string(visit.student_id()) << ", " << std::to_string(visit.lesson_id()) << ", "
      << std::to_string(visit.was_in_class())  << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Visit::delete_visit(int v_id) const {
    std::string query = "DELETE * FROM visit WHERE id=" + std::to_string(v_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

