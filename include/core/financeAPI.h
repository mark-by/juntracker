//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_FINANCEAPI_H
#define CORE_FINANCEAPI_H

class FinanceAPI {
public:
    FinanceAPI();
    std::string getStatistic(Request);
    std::string getPayments(Request);
    templates::Context paymentHistorySerializer(PaymentHistory);
private:
    managerPaymentHistory paymentHistory;
};

#endif //CORE_FINANCEAPI_H
