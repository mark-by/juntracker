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

