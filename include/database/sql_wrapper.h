#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include "abstract_db.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <utils.hpp>

class SqlWrapper : public Database {
public:
    SqlWrapper() : conn(nullptr) {}
    ~SqlWrapper() = default;

    PGconn *getConn();

    void connect() {
        conn = PQconnectdb(get_config("config.txt").c_str());
    }

    void disconnect() {
        close(PQsocket(conn));
    }

    bool query(const std::string& query, PGresult** result) const override;
    [[nodiscard]] bool exec(const std::string& query) const override;
    [[nodiscard]] bool is_connected() const override;
    int count_rows(std::string& table_name) const;

private:
    PGconn *conn;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
