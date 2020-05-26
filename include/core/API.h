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
};


#endif //CORE_API_H
