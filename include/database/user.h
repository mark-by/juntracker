#ifndef INCLUDE_DATABASE_USER_H_
#define INCLUDE_DATABASE_USER_H_

#include "sql_wrapper.h"
#include "lesson.h"
#include "cabinet.h"

enum Permission {
    customer, teacher, admin
};

class User {
public:
    explicit User(int _id, const std::string &_email, const std::string &_login, int _school_id,
                  const std::string &_password, int _permission, const std::string &_avatar)
            : _id(_id), _email(_email), _login(_login), _school_id(_school_id), _password(_password),
              _permission(_permission), _avatar(_avatar) {}

    std::vector<Lesson> get_current_lessons() const;
    std::vector<Lesson> get_lessons_by_weekday(int l_weekday) const;
    std::vector<Student> get_students() const;

    static User get_user(int user_id);
    static User get_user(const std::string &username);
    static int save(const std::string &username, const std::string &password, const std::string &email, int permission);
    static int remove(int user_id);

    int id() const { return _id; }
    std::string email() const { return _email; }
    std::string login() const { return _login; }
    std::string password() const { return _password; }
    int permission() const { return _permission; }
    int school_id() { return _school_id; }

    std::vector<Teacher> get_teachers() const;
    std::vector<cabinet> get_cabinets() const;


private:
    int _id;
    std::string _email;
    std::string _login;
    int _school_id;
    std::string _password;
    int _permission;
    std::string _avatar;

};

#endif  // INCLUDE_DATABASE_USER_H_