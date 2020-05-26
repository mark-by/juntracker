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

Payment Payment::get_payment(int p_id) const {
    std::string query = "SELECT * FROM payment WHERE id=" + std::to_string(p_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int p_student_id = atoi(PQgetvalue(result, 0, 1));
    int p_course_id = atoi(PQgetvalue(result, 0, 2));
    int p_amount = atoi(PQgetvalue(result, 0, 3));
    std::string p_date = std::string(PQgetvalue(result, 0, 4));
    auto res_payment = Payment(p_id, p_student_id, p_course_id, p_amount ,p_date);
    return res_payment;
}

int Payment::add_payment(const Payment& payment) const {
    std::ostringstream s;
    s << "INSERT INTO payment VALUES (" << std::to_string(payment.id()) << ", "
      << std::to_string(payment.student_id()) << ", " << std::to_string(payment.course_id()) << ", "
      << std::to_string(payment.amount()) << ", '" << payment.payment_date() << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Payment::delete_payment(int v_id) const {
    std::string query = "DELETE * FROM payment WHERE id=" + std::to_string(v_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}