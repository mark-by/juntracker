#include "payment_history.h"

std::vector<Payment> PaymentHistory::get_payments_by_student(int s_id) const {
    std::string query = "SELECT * FROM payment WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Payment> res_payments;
    for (int i = 0; i < PQntuples(result); i++) {
        int p_id = atoi(PQgetvalue(result, i, 0));
        int c_id = atoi(PQgetvalue(result, i, 2));
        int p_amount = atoi(PQgetvalue(result, i, 3));
        std::string p_date = PQgetvalue(result, i, 4);
        Payment new_payment(p_id, s_id, c_id, p_amount, p_date);
        res_payments.push_back(new_payment);
    }

    return res_payments;
}

std::vector<Payment> PaymentHistory::get_payments_by_course(int c_id) const {
    std::string query = "SELECT * FROM payment WHERE course_id='" + std::to_string(c_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Payment> res_payments;
    for (int i = 0; i < PQntuples(result); i++) {
        int p_id = atoi(PQgetvalue(result, i, 0));
        int s_id = atoi(PQgetvalue(result, i, 1));
        int p_amount = atoi(PQgetvalue(result, i, 3));
        std::string p_date = PQgetvalue(result, i, 4);
        Payment new_payment(p_id, s_id, c_id, p_amount, p_date);
        res_payments.push_back(new_payment);
    }

    return res_payments;
}
