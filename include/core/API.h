//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_API_H
#define CORE_API_H

#include <string>

#include "ManagerStudent.h"
#include "ManagerVisitHistory.h"
#include "ManagerPaymentHistory.h"
#include "ManagerCourse.h"
#include "ManagerSchedule.h"
#include "ManagerJournal.h"
#include "ManagerVisitHistory.h"

#include "../templates/context/context.h"

class API {
public:
    virtual std::string getMainPage(const std::string&) = 0;
protected:
    ManagerStudent studentManager;
    ManagerVisitHistory visitsManager;
    ManagerPaymentHistory paymentsManager;
    ManagerSchedule scheduleManager;
    ManagerJournal journalManager;

    templates::Context shortStudentSerializer(Student&);
    templates::Context studentSerializer(Student&);
    templates::Context scheduleSerializer(Schedule&);
    templates::Context visitHistorySerializer(VisitHistory&);
    templates::Context paymentSerializer(Payment&);
    templates::Context courseSerializer(Course&);
    templates::Context journalSerializer(Journal&);
};


#endif //CORE_API_H
