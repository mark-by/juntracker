#ifndef JUNTRACKER_COMMON_SQL_H
#define JUNTRACKER_COMMON_SQL_H

#include <sql_wrapper.h>

namespace common {
    namespace query {
        int getSchoolIdByUserId(SqlWrapper &postgres, int id) {
            std::ostringstream query;
            PGresult *result = nullptr;
            query << "select school_id from users where id=" << id << ";";
            postgres.query(query.str(), &result, "Get school id by user id");

            return std::stoi(PQgetvalue(result, 0, 0));
        }
    }
    namespace exec {

    }
}

#endif //JUNTRACKER_COMMON_SQL_H
