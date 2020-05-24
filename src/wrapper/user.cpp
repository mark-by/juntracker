#include "user.h"

User User::check_or_create(std::string& u_login, std::string& u_password, std::string& u_email) {
    std::string query = "SELECT id, password, email FROM users WHERE login='" + u_login + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int res_id = atoi(PQgetvalue(result, 0, 0));
    std::string res_password = PQgetvalue(result, 0, 1);
    std::string res_email = PQgetvalue(result, 0, 2);
    if (res_password == u_password && res_email == u_email ) {
        return User(res_id, res_email, u_login, res_password);
    }
    if (!postgres.query("SELECT COUNT (*) FROM users;", &result)) {
        throw std::exception();
    }
    int next_id = atoi(PQgetvalue(result, 0, 0)) + 1;
    return User(next_id, res_email, u_login, res_password);
}

User User::get_user(int u_id) const {
    std::string query = "SELECT * FROM users WHERE id=" + std::to_string(u_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    std::string u_login = std::string(PQgetvalue(result, 0, 2));
    std::string u_password = std::string(PQgetvalue(result, 0, 3));
    auto res_user = User(u_id, u_email, u_login, u_password);
    return res_user;
}

int User::add_user(const User& user) const {
    std::ostringstream s;
    s << "INSERT INTO users VALUES (" << std::to_string(user.id()) << ", '" << user.email()
    << "', '" << user.login() << "', '" << user.password() << "');";

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

