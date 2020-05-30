#include "payment.h"
#include "utils.hpp"

Student Payment::get_student() const {
    SqlWrapper db;

    db << "SELECT student.id, student.name, student.surname, student.age, student.description FROM student "
        << "join payment on payment.student_id=student.id where payment.id" << _id << ";";
    db.query("Get student by payment id");
    db.disconnect();

    return Student(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_str(4, 0),
            db.get_str(5, 0),
            db.get_str(6, 0)
            );
}

Course Payment::get_course() const {
    SqlWrapper db;

    db << "select course.id, course.name, course.price, course.school_id, course.teacher_id from course"
          << "join payment on payment.course_id = course.id where payment.id" << _id << ";";
    db.query("Get course by payment id");
    db.disconnect();
    return Course(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_int(2, 0),
            db.get_int(3, 0),
            db.get_int(4, 0)
            );
}

Payment Payment::get_payment(int payment_id) {
    SqlWrapper db;

    db << "select * from payment where id=" << payment_id << ";";
    db.query("Get payment");
    db.disconnect();

    return Payment(
            db.get_int(0, 0),
            db.get_int(1, 0),
            db.get_int(2, 0),
            db.get_int(3, 0),
            db.get_str(4, 0),
            db.get_int(5, 0)
            );
}

int Payment::save(int student_id, int course_id, int amount, std::string& payment_date, int school_id) {
    SqlWrapper db;
    db << "insert into payment (student_id, course_id, amount, payment_date, school_id) values("
        << student_id << ", " << course_id << ", " << amount << ", '"
        << payment_date << "', " << school_id << ");";
    db.exec("Save payment");
    db.disconnect();

    return 0;
}

int Payment::remove(int payment_id) {
    SqlWrapper db;

    db << "DELETE FROM payment WHERE id=" << payment_id << ";";
    db.exec("Delete from payment");
    db.disconnect();

    return 0;
}