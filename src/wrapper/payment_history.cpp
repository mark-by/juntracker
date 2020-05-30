#include "payment_history.h"

std::vector<Payment> PaymentHistory::get_payments_by_student(int s_id) const {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);

    db << "SELECT * FROM payment WHERE student_id=" << s_id << ";";
    db.exec("Get all payments by student");

    std::vector<Payment> res_payments;
    res_payments.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_payments.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                converter.convert(db.get_str(4, i)),
                db.get_int(5, i)
        );
    }
    db.disconnect();

    return res_payments;
}

std::vector<Payment> PaymentHistory::get_payments_by_course(int c_id) const {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);

    db << "SELECT * FROM payment WHERE course_id=" << c_id << ";";
    db.exec("Get all payments for course");
    std::vector<Payment> res_payments;
    res_payments.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_payments.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                converter.convert(db.get_str(4, i)),
                db.get_int(5, i));
    }
    db.disconnect();

    return res_payments;
}
