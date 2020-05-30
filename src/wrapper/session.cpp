#include "session.h"
#include <utils.hpp>

User Session::get_user(const std::string& s_cookie) {
    SqlWrapper db;

    db << "select users.id, email, login, school_id, password, permission, avatar from users "
       << "join session on session.user_id=users.id"
       << "where session.cookie='" << s_cookie << "';";
    db.exec("Get user");
    db.disconnect();

    return User(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_str(4, 0),
            db.get_int(5, 0),
            db.get_str(6, 0)
            );
}

Session Session::create_session(const std::string& username, const std::string& password) {
    SqlWrapper db;

    db << "select password from users where login='" << username << "';";
    db.exec("Compare passwords");
    if (strcmp(db.get_str(0), password.c_str()) != 0) {
        db.disconnect();
        throw std::exception();
    }

    db << "SELECT id FROM users WHERE login='" << username << "';";
    db.exec("Get id by login");
    int user_id = db.get_int(0);

    std::string new_cookie = username;

    db << "insert into session (cookie, user_id) "
       << "values ('" << new_cookie << "', " << user_id << ";";
    db.exec("Create session");

    db << "select id, cookie from session";
    db.exec("Get session");
    db.disconnect();

    return Session(db.get_int(0), db.get_str(1));
}

int Session::remove(int user_id) {
    SqlWrapper db;

    db << "delete from session where user_id=" << user_id << ";";
    db.exec("Remove session");
    db.disconnect();

    return 0;
}

int Session::remove(const std::string cookie) {
    SqlWrapper db;

    db << "delete from session where cookie='" << cookie << "';";
    db.exec("Remove session");
    db.disconnect();

    return 0;
}

