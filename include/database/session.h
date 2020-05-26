#ifndef DATABASE_SESSION_H
#define DATABASE_SESSION_H

#include "user.h"

class Session {
 public:
    Session(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Session(int _id, std::string& _cookie, SqlWrapper postgres)
            : _id(_id)
            , _cookie(_cookie) {}

    static User get_user(const std::string& s_cookie);

    static Session create_session(const std::string& username, const std::string& password);
    static int remove(int user_id);
    static int remove(const std::string cookie);

    int id() const { return _id; }
    std::string cookie() const { return _cookie; }

 private:
    int _id;
    std::string _cookie;

    SqlWrapper postgres;
};

#endif  // DATABASE_SESSION_H
