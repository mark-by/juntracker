#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <vector>

#include "sql_wrapper.h"

class User {
 public:
   User(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit User(int _id, std::string& _email, std::string& _login, std::string& _status,  std::string& _password)
            : _id(_id)
            , _email(_email)
            , _login(_login)
            , _status(_status)
            , _password(_password) {}

    std::string get_status(int u_id) const;
    User get_user(int u_id) const;
    int add_user(const User& user) const;
    int delete_user(int u_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] std::string email() const { return _email; }
    [[nodiscard]] std::string login() const { return _login; }
    [[nodiscard]] std::string status() const { return _status; }
    [[nodiscard]] std::string password() const { return _password; }

 private: 
    int _id;
    std::string _email;
    std::string _login;
    std::string _status;
    std::string _password;

    SqlWrapper postgres;
};

#endif  // _USER_H_