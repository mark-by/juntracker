#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <vector>

#include "sql_wrapper.h"

class User {
 public:
   User(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit User(int id, std::string& email, std::string& login, std::string& status)
            : id(id)
            , email(email)
            , login(login)
            , status(status) {}

    std::string get_status(int u_id) const;

 private: 
    int id;
    std::string email;
    std::string login;
    std::string status;

    SqlWrapper postgres;
};

#endif  // _USER_H_