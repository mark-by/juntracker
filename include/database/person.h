#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

#include "sql_wrapper.h"

class Person {
 public:
    [[nodiscard]] virtual std::string get_name(int id) const = 0;
    [[nodiscard]] virtual std::string get_surname(int id) const = 0;

    [[nodiscard]] virtual int id() const = 0;
    [[nodiscard]] virtual std::string name() const = 0;
    [[nodiscard]] virtual std::string surname() const = 0;
};

#endif  // _PERSON_H_