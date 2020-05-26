//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_API_H
#define CORE_API_H

#include <string>
#include <../database/student.h>
#include <../database/lesson.h>
#include "../templates/context/context.h"

class API {


public:
    virtual std::string getMainPage(int user_id) = 0;
protected:

    templates::Context shortStudentSerializer(Student&);
    templates::Context studentSerializer(Student&);
    templates::Context visitHistorySerializer(VisitHistory&);
    templates::Context paymentSerializer(Payment&);
    templates::Context courseSerializer(Course&);
    templates::Context journalSerializer(Journal&);
};


#endif //CORE_API_H
