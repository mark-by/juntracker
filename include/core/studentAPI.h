//
// Created by timofei on 14.04.2020.
//

#include "response.h"

#ifndef CORE_CORE_H
#define CORE_CORE_H

class StudentAPI {
public:
    StudentAPI();
    Response getStudent(std::string);
    response::Context studentSerializer(Student);
    
private:
    managerStudent student;
    managerVisitHistory visits;
    managerPaymentHistory payments;
};

#endif // CORE_CORE_H
