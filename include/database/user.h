#ifndef INCLUDE_DATABASE_USER_H_
#define INCLUDE_DATABASE_USER_H_

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

    std::vector<Lesson> get_current_lessons() const;
    std::vector<Lesson> get_lessons_by_weekday(int l_weekday) const;
    Student get_student() const;

    static User get_user(int user_id);
    static int save(const std::string& username, const std::string& password, const std::string& email);
    static int remove(int user_id);

    int id() const { return _id; }
    std::string email() const { return _email; }
    std::string login() const { return _login; }
    std::string password() const { return _password; }

 private: 
    int _id;
    std::string _email;
    std::string _login;
    std::string _password;

    SqlWrapper postgres;
};

#endif  // INCLUDE_DATABASE_USER_H_