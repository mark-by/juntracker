#ifndef _PAYMENT_H_
#define _PAYMENT_H_

#include "sql_wrapper.h"

class Payment {
 public:
    Payment(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Payment(int _id, int _student_id, int _course_id, int _amount, std::string& _payment_date)
            : _id(_id)
            , _student_id(_student_id)
            , _course_id(_course_id)
            , _amount(_amount)
            , _payment_date(_payment_date) {}
    
    int get_student_id(int p_id) const;
    int get_course_id(int p_id) const;


    Payment get_payment(int p_id) const;
    int add_payment(const Payment& payment) const;
    int delete_payment(int p_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] int student_id() const { return _student_id; }
    [[nodiscard]] int course_id() const { return _course_id; }
    [[nodiscard]] int amount() const { return _amount; }
    [[nodiscard]] std::string payment_date() const { return _payment_date; }

 private:
    int _id;
    int _student_id;
    int _course_id;
    int _amount;
    std::string _payment_date;

    SqlWrapper postgres;
};

#endif  // _PAYMENT_H_