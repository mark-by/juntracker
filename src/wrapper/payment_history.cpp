#include "payment_history.h"

std::vector<Payment> PaymentHistory::get_payments_by_student(int s_id) const {
    SqlWrapper postgres;
    std::string query = "SELECT * FROM payment WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::vector<Payment> res_payments;
    for (int i = 0; i < PQntuples(result); i++) {
        int p_id = atoi(PQgetvalue(result, i, 0));
        int p_amount = atoi(PQgetvalue(result, i, 3));
        std::string p_date = PQgetvalue(result, i, 4);
        Payment new_payment(p_id, p_amount, p_date, postgres);
        res_payments.push_back(new_payment);
    }
    postgres.disconnect();
    return res_payments;
}

std::vector<Payment> PaymentHistory::get_payments_by_course(int c_id) const {
    SqlWrapper postgres;
    std::string query = "SELECT * FROM payment WHERE course_id='" + std::to_string(c_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::vector<Payment> res_payments;
    for (int i = 0; i < PQntuples(result); i++) {
        int p_id = atoi(PQgetvalue(result, i, 0));
        int p_amount = atoi(PQgetvalue(result, i, 3));
        std::string p_date = PQgetvalue(result, i, 4);
        Payment new_payment(p_id, p_amount, p_date, postgres);
        res_payments.push_back(new_payment);
    }
    postgres.disconnect();
    return res_payments;
}
