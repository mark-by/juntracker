#ifndef INCLUDE_DATABASE_PAYMENT_H_
#define INCLUDE_DATABASE_PAYMENT_H_

#include "sql_wrapper.h"
#include "course.h"

class Payment {
 public:
    Payment(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Payment(int _id, int _amount, std::string& _payment_date, SqlWrapper postgres)
            : _id(_id)
            , _amount(_amount)
            , _payment_date(_payment_date) {}
    
    Student get_student() const;
    Course get_course() const;


    static Payment get_payment(int payment_id);
    static int save(int student_id, int course_id, int amount);
    static int remove(int payment_id);

    int id() const { return _id; }
    int amount() const { return _amount; }
    std::string payment_date() const { return _payment_date; }

 private:
    int _id;
    int _amount;
    std::string _payment_date;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_PAYMENT_H_