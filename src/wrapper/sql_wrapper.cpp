#include "sql_wrapper.h"
#include <iostream>

std::string strError(PGconn *conn, PGresult *result, char *exec, const std::string &comment) {
    std::ostringstream error;
    error << "EXEC " << exec << std::endl << "ERROR: " << PQerrorMessage(conn) << std::endl << "STATUS: "
          << PQresultStatus(result) << std::endl;
    if (!comment.empty()) {
        error << "FAIL: " << comment << std::endl;
    }
    delete[] exec;
    return error.str();
}

bool SqlWrapper::query(const std::string &query, PGresult **result, const std::string &comment) {
    char *cstr = new char[query.length() + 1];
    std::strcpy(cstr, query.c_str());
    *result = PQexec(conn, cstr);
    if (PQresultStatus(*result) != PGRES_TUPLES_OK) {
        disconnect();
        throw std::runtime_error(strError(conn, *result, cstr, comment))
    }
    delete[] cstr;
    return true;
}

bool SqlWrapper::exec(const std::string &query, const std::string &comment) {
    char *cstr = new char[query.length() + 1];
    std::strcpy(cstr, query.c_str());
    auto result = PQexec(conn, cstr);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        disconnect();
        throw std::runtime_error(strError(conn, result, cstr, comment));
    }
    delete[] cstr;
    return true;
}

bool SqlWrapper::check_connect() {
    if (PQstatus(conn) != CONNECTION_OK) {
        disconnect();
        throw std::runtime_error("ERROR: DATABASE NOT CONNECTED");
    }
}

PGconn *SqlWrapper::getConn() {
    return conn;
}

void SqlWrapper::disconnect() {
    close(PQsocket(conn));
}
