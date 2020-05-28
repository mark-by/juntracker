#include "sql_wrapper.h"
#include <iostream>

// SqlWrapper is ...
SqlWrapper::SqlWrapper(PGconn *conn)
    : conn(conn) {}

bool SqlWrapper::query(const std::string& query, PGresult** result) const {
    char * cstr = new char[query.length() + 1];
    std::strcpy(cstr, query.c_str());
    *result = PQexec(conn, cstr);
    if (PQresultStatus(*result) != PGRES_TUPLES_OK) {
        std::cout << "CSTR " << cstr << std::endl;
        std::cout << "ERROR:" << PQerrorMessage(conn) << std::endl;
        std::cout << "STATUS:" << PQresultStatus(*result) << std::endl;
        return false;
    }
    delete[] cstr;
    return true;
}

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

bool SqlWrapper::exec(const std::string& query) const {
    char * cstr = new char[query.length() + 1];
    std::strcpy(cstr, query.c_str());
//    auto it = query.rbegin();
//    it++;
//    if (*it == ')') {
//        it++;
//        if (*it == '\'') {
//            std::strcat(cstr, "');");
//        }
//    }
    auto result = PQexec(conn, cstr);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cout << "CSTR " << cstr << std::endl;
        std::cout << "ERROR:" << PQerrorMessage(conn) << std::endl;
        std::cout << "STATUS:" << PQresultStatus(result) << std::endl;
        return false;
    }
    delete[] cstr;
    return true;
}

bool SqlWrapper::is_connected() const {
    return !(PQstatus(conn) != CONNECTION_OK);
}

int SqlWrapper::count_rows(std::string& table_name) const {
    auto _postgres = conntect();
    std::string command = "SELECT COUNT(*) FROM " + table_name + ";";
    PGresult *result = nullptr;
    if (!query(command, &result)) {
        throw std::exception();
    }
    int rows = atoi(PQgetvalue(result, 0, 0));
    return rows;
}

PGconn *SqlWrapper::getConn() {
    return conn;
}
