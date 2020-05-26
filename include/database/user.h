#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "sql_wrapper.h"
#include "lesson.h"

class User {
 public:
    User(SqlWrapper& postgres)
        : postgres(postgres) {}
    explicit User(int _id, std::string& _email, std::string& _login,  std::string& _password)
        : _id(_id)
        , _email(_email)
        , _login(_login)
        , _password(_password) {}

    User check_or_create(std::string& u_login, std::string& u_password, std::string& u_email);
    std::vector<Lesson> get_current_lessons() const;
    std::vector<Lesson> get_lessons_by_weekday(std::string l_weekday) const;


    User get_user(int u_id) const;
    int add_user(const User& user) const;
    int delete_user(int u_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] std::string email() const { return _email; }
    [[nodiscard]] std::string login() const { return _login; }
    [[nodiscard]] std::string password() const { return _password; }

 private: 
    int _id;
    std::string _email;
    std::string _login;
    std::string _password;

    SqlWrapper postgres;
};

#endif  // _USER_H_