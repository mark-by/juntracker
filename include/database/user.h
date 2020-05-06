#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <vector>

class User {
 public:
    explicit User();
    std::string get_status() const;

 private: 
    int id;
    std::string email;
    std::string login;
    std::string password;
    std::string status;
};

#endif  // _USER_H_