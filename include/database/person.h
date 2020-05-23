#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

#include "sql_wrapper.h"

class Person {
 public:
    virtual std::string get_name(int id) const = 0;
    virtual std::string get_surname(int id) const = 0;
};

#endif  // _PERSON_H_