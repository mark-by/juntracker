#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

class Person {
 public:
    virtual std::string get_name() const;
    virtual std::string get_surname() const;
 private:
    int id;
    std::string name;
    std::string surname;
};

#endif  // _PERSON_H_