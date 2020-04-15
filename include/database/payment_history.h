#ifndef _PAYMENT_HISTORY_H_
#define _PAYMENT_HISTORY_H_

#include <string>
#include <vector>

#include "payment.h"

class PaymentHistory {
 public:
    explicit PaymentHistory();
    std::vector<Payment> get_payments_by_student(int id) const;
    std::vector<Payment> get_payments_by_course(int id) const;
    std::vector<Payment> get_payments_by_pass(std::string start, std::string end) const;

 private:
    std::vector<Payment> payments;
};

#endif  // _PAYMENT_HISTORY_H_