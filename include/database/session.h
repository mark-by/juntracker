#ifndef _COOKIE_H
#define _COOKIE_H

#include "user.h"
#include "sql_wrapper.h"

class Session {
 public:
    Session(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit Session(int _id, std::string& _cookie, int uid)
            : _id(_id)
            , _cookie(_cookie)
            , _uid(uid) {}

    User get_user(const std::string& s_cookie);

    Session get_session(int s_id) const;
    int add_session(const Session& session) const;
    int delete_session(int s_id) const;

    [[nodiscard]] int id() const { return _id; }
    [[nodiscard]] std::string cookie() const { return _cookie; }
    [[nodiscard]] int uid() const { return _uid; }

 private:
    int _id;
    std::string _cookie;
    int _uid;

    SqlWrapper postgres;
};

#endif  // _COOKIE_H
