#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include <postgresql/libpq-fe.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class PGConnection {
public:
    PGConnection();
    std::shared_ptr<PGconn> connection() const;

private:
    std::string m_dbhost = "localhost";
    int         m_dbport = 5432;
    std::string m_dbname = "jun_tracker";
    std::string m_dbuser = "amavrin";
    std::string m_dbpass = "root";
    std::shared_ptr<PGconn>  m_connection;
};

class SqlWrapper {
private:
    PGconn *conn;
    std::shared_ptr<PGConnection> m_connection;

public:
    explicit SqlWrapper() {}
    explicit SqlWrapper(PGconn *conn);
    ~SqlWrapper();

    [[nodiscard]] bool is_select(const std::string& query) const;
    bool query(const std::string& query, PGresult** result) const ;
    bool exec(const std::string& query);
    [[nodiscard]] bool is_connected() const;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
