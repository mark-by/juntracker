//
// Created by gg on 30.05.2020.
//

#include "Cabinet.h"
#include "sql_wrapper.h"


void Cabinet::save(const std::string &title, int schoolId) {
    SqlWrapper postgres;
    std::ostringstream s;
    s << "INSERT INTO cabinet(title, school_id) VALUES ('" << title << "', " << schoolId << ");";

    postgres.exec(s.str(), "Save cabinet");
    postgres.disconnect();
}

void Cabinet::remove(int id) {
    SqlWrapper postgres;
    std::ostringstream query;
    query << "DELETE FROM cabinet WHERE id=" << id << ";";
    postgres.exec(query.str(), "Remove cabinet");
    postgres.disconnect();
}

Cabinet Cabinet::get(int id) {
    SqlWrapper postgres;
    std::ostringstream query;
    query << "select * FROM cabinet WHERE id=" << id << ";";
    PGresult *result = nullptr;
    postgres.query(query.str(), &result, "Get user by username");
    postgres.disconnect();

    return Cabinet(
            std::stoi(PQgetvalue(result, 0, 0)),
            std::stoi(PQgetvalue(result, 0, 2)),
            PQgetvalue(result, 0, 1)
            );
}
