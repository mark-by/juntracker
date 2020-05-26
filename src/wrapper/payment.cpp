#include "payment.h"

Student Payment::get_student() const {
    std::string query = "SELECT student_id FROM payment WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int student_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM student WHERE id=" + std::to_string(student_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int s_age = atoi(PQgetvalue(result, 0, 3));
    auto res_student = Student(student_id, s_name, s_surname, s_age, postgres);
    return res_student;
}

Course Payment::get_course() const {
    std::string query = "SELECT course_id FROM payment WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int course_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM course WHERE id=" + std::to_string(course_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string name = std::string(PQgetvalue(result, 0, 1));
    int price = atoi(PQgetvalue(result, 0, 2));
    auto res_course = Course(course_id, name, price, postgres);
    return res_course;
}

Payment Payment::get_payment(int payment_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "SELECT * FROM payment WHERE id=" + std::to_string(payment_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    int p_amount = atoi(PQgetvalue(result, 0, 3));
    std::string p_date = std::string(PQgetvalue(result, 0, 4));
    auto res_payment = Payment(payment_id, p_amount, p_date, postgres);
    return res_payment;
}

int Payment::save(int student_id, int course_id, int amount) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::ostringstream s;
    std::string table_name = "payment";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO payment VALUES (" << std::to_string(count_rows + 1) << ", "
      << std::to_string(student_id) << ", " << std::to_string(course_id) << ", "
      << std::to_string(amount) << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Payment::remove(int payment_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "DELETE FROM payment WHERE id=" + std::to_string(payment_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}