#ifndef INCLUDE_DATABASE_USER_H_
#define INCLUDE_DATABASE_USER_H_

#include "sql_wrapper.h"
#include "lesson.h"

enum Permission { customer, teacher, admin };

class User {
 public:
    explicit User(int _id, std::string& _email, std::string& _login,  std::string& _password, int _permission)
        : _id(_id)
        , _email(_email)
        , _login(_login)
        , _password(_password)
        , _permission(_permission) {}

    std::vector<Lesson> get_current_lessons() const;
    std::vector<Lesson> get_lessons_by_weekday(int l_weekday) const;
    std::vector<Student> get_students() const;

    static User get_user(int user_id);
    static User get_user(const std::string& username);
    static int save(const std::string& username, const std::string& password, const std::string& email);
    static int remove(int user_id);

    int id() const { return _id; }
    std::string email() const { return _email; }
    std::string login() const { return _login; }
    std::string password() const { return _password; }
    int permission() const { return _permission; }

 private: 
    int _id;
    std::string _email;
    std::string _login;
    std::string _password;

    int _permission;
};

#endif  // INCLUDE_DATABASE_USER_H_