#include "session.h"

User Session::get_user(const std::string& s_cookie) {
    std::string query = "SELECT * FROM users WHERE cookie=" + s_cookie + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    int s_uid = atoi(PQgetvalue(result, 0, 0));
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    std::string u_login = std::string(PQgetvalue(result, 0, 2));
    std::string u_password = std::string(PQgetvalue(result, 0, 3));
    auto res_user = User(s_uid, u_email, u_login, u_password);
    return res_user;
}

Session Session::get_session(int s_id) const {
    std::string query = "SELECT * FROM session WHERE id=" + std::to_string(s_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string s_cookie = std::string(PQgetvalue(result, 0, 1));
    int s_uid = atoi(PQgetvalue(result, 0, 2));
    auto res_session = Session(s_id, s_cookie, s_uid);
    return res_session;
}

int Session::add_session(const Session& session) const {
    std::ostringstream s;
    s << "INSERT INTO session VALUES (" << std::to_string(session.id()) << ", '"
    << session.cookie() << "', " << std::to_string(session.uid()) << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Session::delete_session(int s_id) const {
    std::string query = "DELETE * FROM session WHERE id=" + std::to_string(s_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

