//
// Created by timofei on 22.04.2020.
//

#include "../../include/core/API.h"
#include "../../include/templates/context/context.h"

API::API() {}

templates::Context API::shortStudentSerializer(Student) {}

templates::Context API::studentSerializer(Student) {}

templates::Context API::scheduleSerializer(Schedule) {}

templates::Context API::visitHistorySerializer(VisitHistory) {}

templates::Context API::paymentHistorySerializer(PaymentHistory) {}

templates::Context API::courseSerializer(Course) {}

templates::Context API::journalSerializer(Journal) {}