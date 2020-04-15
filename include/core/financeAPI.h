//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_FINANCEAPI_H
#define CORE_FINANCEAPI_H

class FinanceAPI {
public:
    FinanceAPI();
    std::string getStatistic(std::string);
    std::string getPayments(std::string);
    templates::Context paymentHistorySerializer(PaymentHistory);
private:
    managerPaymentHistory paymentHistory;
};

#endif //CORE_FINANCEAPI_H
