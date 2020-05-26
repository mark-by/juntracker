//
// Created by timofei on 23.04.2020.
//

#ifndef CORE_MANAGERSTUDENT_H
#define CORE_MANAGERSTUDENT_H

#include <string>

class ManagerStudent {
public:
    int addStudent(const std::string& name, const std::string& surname, const std::string& age);
    int deleteStudent(const std::string&);
};

#endif //CORE_MANAGERSTUDENT_H
