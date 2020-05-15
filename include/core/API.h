//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_API_H
#define CORE_API_H

#include "ManagerStudent.h"
#include "ManagerPaymentHistory.h"
#include "ManagerCourse.h"
#include "ManagerSchedule.h"
#include "ManagerJournal.h"
#include "ManagerVisitHistory.h"

class API {
public:
    virtual std::string getMainPage(const std::string&) = 0;

protected:
    ManagerStudent studentManager;
    ManagerVisitHistory visitsManager;
    ManagerPaymentHistory paymentsManager;
    ManagerSchedule scheduleManager;
    ManagerJournal journalManager;

    templates::Context shortStudentSerializer(Student);
    templates::Context studentSerializer(Student);
    templates::Context scheduleSerializer(Schedule);
    templates::Context visitHistorySerializer(VisitHistory);
    templates::Context paymentHistorySerializer(PaymentHistory);
    templates::Context courseSerializer(Course);
    templates::Context journalSerializer(Journal);
};


#endif //CORE_API_H
