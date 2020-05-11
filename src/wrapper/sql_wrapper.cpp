#include "sql_wrapper.h"

// PGConnection is ...
PGConnection::PGConnection() {
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(),
            std::to_string(m_dbport).c_str(),
            nullptr,
            nullptr,
            m_dbname.c_str(),
            m_dbuser.c_str(),
            m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 ) {
        throw std::runtime_error( PQerrorMessage( m_connection.get() ) );
    }
}

std::shared_ptr<PGconn> PGConnection::connection() const {
    return m_connection;
}

// SqlWrapper is ...
SqlWrapper::SqlWrapper(PGconn *conn)
    : conn(conn) {}

SqlWrapper::~SqlWrapper() = default;

bool SqlWrapper::query(const std::string& query, PGresult** result) const {
    *result = PQexec(conn, query.c_str());
    if (PQresultStatus(*result) != PGRES_TUPLES_OK) {
        return false;
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
    return true;
}

bool SqlWrapper::exec(const std::string& query) {
    auto result = PQexec(conn, query.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        return false;
    }
    return true;
}

bool SqlWrapper::is_connected() const {
    if (PQstatus(conn) != CONNECTION_OK) {
        return false;
    }
    return true;
}

bool SqlWrapper::is_select(const std::string& query) const {
    if (query.find("SELECT") != std::string::npos) {
        return true;
    }
    return false;
}
