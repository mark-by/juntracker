#ifndef _PAYMENT_H_
#define _PAYMENT_H_

#include <string>

class Payment {
 public:
    explicit Payment();
    
    int get_student_id() const;
    int get_course_id() const;
 private:
    int id;
    int student_id;
    int course_id;
    int amount;
    std::string payment_date;
};

#endif  // _PAYMENT_H_