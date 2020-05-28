#include "payment.h"
#include "utils.hpp"

Student Payment::get_student() const {
    SqlWrapper postgres;
    std::string query = "SELECT student_id FROM payment WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int student_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM student WHERE id=" + std::to_string(student_id) + ";";
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int s_age = atoi(PQgetvalue(result, 0, 3));
    postgres.disconnect();
    return Student(student_id, s_name, s_surname, s_age);
}

Course Payment::get_course() const {
    SqlWrapper postgres;
    std::string query = "SELECT course_id FROM payment WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int course_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM course WHERE id=" + std::to_string(course_id) + ";";
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string name = std::string(PQgetvalue(result, 0, 1));
    int price = atoi(PQgetvalue(result, 0, 2));
    postgres.disconnect();
    return Course(course_id, name, price);
}

Payment Payment::get_payment(int payment_id) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM payment WHERE id=" + std::to_string(payment_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }

    int p_amount = atoi(PQgetvalue(result, 0, 3));
    std::string p_date = std::string(PQgetvalue(result, 0, 4));
    postgres.disconnect();
    return Payment(payment_id, p_amount, p_date, postgres);
}

int Payment::save(int student_id, int course_id, int amount) {
    SqlWrapper postgres;;

    std::ostringstream s;
    std::string table_name = "payment";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO payment VALUES (" << std::to_string(count_rows + 1) << ", "
      << std::to_string(student_id) << ", " << std::to_string(course_id) << ", "
      << std::to_string(amount) << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int Payment::remove(int payment_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM payment WHERE id=" + std::to_string(payment_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}