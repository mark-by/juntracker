#include "session.h"
#include <utils.hpp>

User Session::get_user(const std::string& s_cookie) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM session WHERE cookie='" + s_cookie + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }

    int s_uid = atoi(PQgetvalue(result, 0, 2));
    query = "SELECT * FROM users WHERE id=" + std::to_string(s_uid) + ";";

    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    std::string u_login = std::string(PQgetvalue(result, 0, 2));
    std::string u_password = std::string(PQgetvalue(result, 0, 3));
    postgres.disconnect();
    return User(s_uid, u_email, u_login, u_password);
}

Session Session::create_session(const std::string& username, const std::string& password) {
    SqlWrapper postgres;
    std::string query = "SELECT password FROM users WHERE login='" + username + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    char *res_password = PQgetvalue(result, 0, 0);
    if (strcmp(res_password, password.c_str())) {
        postgres.disconnect();
        throw std::exception();
    }

    query = "SELECT id FROM users WHERE login='" + username + "';";
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int user_id = atoi(PQgetvalue(result, 0, 0));

    std::ostringstream s;
    std::string table_name = "session";
    std::string new_cookie = username;
    int count_rows = postgres.count_rows(table_name);

    s << "INSERT INTO session VALUES (" << count_rows + 1 << ", '"
      << new_cookie << "', " << user_id << ");";

    query = s.str();
    if (!postgres.exec(query)) {
        postgres.disconnect();
        throw std::exception();
    }
    postgres.disconnect();
    return Session(count_rows + 1, new_cookie);
}

int Session::remove(int user_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM session WHERE user_id=" + std::to_string(user_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int Session::remove(const std::string cookie) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM session WHERE cookie=" + cookie + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

