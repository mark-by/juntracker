//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_TEACHERAPI_H
#define CORE_TEACHERAPI_H

#include <string>
#include <unordered_map>
#include <StaffAPI.h>

class TeacherAPI: public StaffAPI {
public:
    TeacherAPI();
    int rate(std::unordered_map<std::string, std::string> &);//
};


#endif //CORE_TEACHERAPI_H
