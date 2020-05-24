#include "day.h"

std::string Day::get_weekday(std::string d_date) const {
    std::string query = "SELECT weekday FROM day WHERE date='" + d_date + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string res_weekday = PQgetvalue(result, 0, 0);
    return res_weekday;
}

Day Day::get_day(int d_id) const {
    std::string query = "SELECT * FROM day WHERE id=" + std::to_string(d_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string d_weekday = std::string(PQgetvalue(result, 0, 1));
    std::string d_date = std::string(PQgetvalue(result, 0, 2));
    auto res_day = Day(d_id, d_weekday, d_date);
    return res_day;
}

int Day::add_day(const Day& day) const {
    std::ostringstream s;
    s << "INSERT INTO day VALUES (" << std::to_string(day.id()) << ", '"
      << day.weekday() << "', '" << day.date() << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Day::delete_day(int d_id) const {
    std::string query = "DELETE * FROM day WHERE id=" + std::to_string(d_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}