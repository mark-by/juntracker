//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/financeAPI.h"

FinanceAPI::FinanceAPI() {}

std::string FinanceAPI::getStatistic(Request) {}

std::string FinanceAPI::getPayments(Request) {}

templates::Context FinanceAPI::paymentHistorySerializer(PaymentHistory) {}
