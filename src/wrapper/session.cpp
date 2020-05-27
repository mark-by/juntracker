#include "session.h"
#include <utils.hpp>

User Session::get_user(const std::string& s_cookie) {
    auto postgres = connect();

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

Session Session::create_session(const std::string& username, const std::string& password) {
    auto postgres = connect();
    std::string query = "SELECT password FROM users WHERE login='" + username + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string res_password = PQgetvalue(result, 0, 0);
    if (res_password != password) {
        throw std::exception();
    }

    query = "SELECT user_id FROM users WHERE login='" + username + "';";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int user_id = atoi(PQgetvalue(result, 0, 0));

    std::string new_cookie = username;
    std::ostringstream s;
    std::string table_name = "session";
    int count_rows = postgres.count_rows(table_name);

    s << "INSERT INTO sesion VALUES (" << std::to_string(count_rows + 1) << ", '"
      << new_cookie << "', " << std::to_string(user_id)  << ");";

    query = s.str();
    if (!postgres.exec(query)) {
        throw std::exception();
    }
    return Session(count_rows + 1, new_cookie, postgres);
}

int Session::remove(int user_id) {
    auto postgres = connect();

    std::string query = "DELETE FROM session WHERE user_id=" + std::to_string(user_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Session::remove(const std::string cookie) {
    auto postgres = connect();

    std::string query = "DELETE FROM session WHERE cookie=" + cookie + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

