#include "user.h"

std::string User::get_status(int u_id) const {
    std::string query = "SELECT status FROM users WHERE id='" + std::to_string(u_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string u_status = PQgetvalue(result, 0, 0);
    return u_status;
}

User User::get_user(int u_id) const {
    std::string query = "SELECT * FROM users WHERE id=" + std::to_string(u_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    std::string u_login = std::string(PQgetvalue(result, 0, 2));
    std::string u_status = std::string(PQgetvalue(result, 0, 3));
    std::string u_password = std::string(PQgetvalue(result, 0, 4));
    auto res_user = User(u_id, u_email, u_login, u_status, u_password);
    return res_user;
}

int User::add_user(const User& user) const {
    std::ostringstream s;
    s << "INSERT INTO users VALUES (" << std::to_string(user.id()) << ", '" << user.email()
    << "', '" << user.login() << "', '" << user.status() << "', '" << user.password() << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int User::delete_user(int u_id) const {
    std::string query = "DELETE * FROM users WHERE id=" + std::to_string(u_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

