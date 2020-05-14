#include "sql_wrapper.h"

// SqlWrapper is ...
SqlWrapper::SqlWrapper(PGconn *conn)
    : conn(conn) {}

SqlWrapper::~SqlWrapper() = default;

bool SqlWrapper::query(const std::string& query, PGresult** result) const {
    *result = PQexec(conn, query.c_str());
    return !(PQresultStatus(*result) != PGRES_TUPLES_OK);

//    for (int i = 0; i < PQnfields(result); i++) {
//        std::cout << PQfname(result, i) << "         ";
//    }
//    std::cout << std::endl;
//    // print column values
//    for (int i = 0; i < PQntuples(result); i++) {
//        for (int j = 0; j < PQnfields(result); j++) {
//            std::cout << PQgetvalue(result, i, j) << "   ";
//        }
//        std::cout << std::endl;
//    }
}

bool SqlWrapper::exec(const std::string& query) const {
    auto result = PQexec(conn, query.c_str());
    return !(PQresultStatus(result) != PGRES_COMMAND_OK);
}

bool SqlWrapper::is_connected() const {
    return !(PQstatus(conn) != CONNECTION_OK);
}

bool SqlWrapper::is_select(const std::string& query) const {
    return query.find("SELECT") != std::string::npos;
}
