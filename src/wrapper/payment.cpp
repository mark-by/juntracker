
#include "payment.h"

int Payment::get_student_id(int p_id) const {
    std::string query = "SELECT student_id FROM payment WHERE id='" + std::to_string(p_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int s_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return s_id;
}

int Payment::get_course_id(int p_id) const {
    std::string query = "SELECT course_id FROM payment WHERE id='" + std::to_string(p_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int c_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return c_id;
}

int Payment::add_payment(int p_id, int s_id, int c_id, int p_amount, const std::string& date) {
    std::ostringstream s;
    s << "INSERT INTO payment VALUES (" << std::to_string(p_id) << ", "
    << std::to_string(s_id) << ", " << std::to_string(c_id) << ", "
    << std::to_string(p_amount) << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
       return -1;
    }
    return 0;
}