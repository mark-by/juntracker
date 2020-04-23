//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_API_H
#define CORE_API_H

#include "managerStudent.h"
#include "managerVisitHistory"
#include "managerPaymentHistory.h"
#include "managerCourse.h"
#include "managerSchedule.h"
#include "managerJournal.h"

class API {
public:
    virtual std::string getMainPage(std::string) = 0;

protected:
    managerStudent studentManager;
    managerVisitHistory visitsManager;
    managerPaymentHistory paymentsManager;
    managerSchedule scheduleManager;
    managerJournal journalManager;

    templates::Context shortStudentSerializer(Student);
    templates::Context studentSerializer(Student);
    templates::Context scheduleSerializer(Schedule);
    templates::Context visitHistorySerializer(VisitHistory);
    templates::Context paymentHistorySerializer(PaymentHistory);
    templates::Context courseSerializer(Course);
    templates::Context journalSerializer(Journal);
};


#endif //CORE_API_H
