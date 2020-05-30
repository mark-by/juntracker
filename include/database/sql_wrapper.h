#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <utils.hpp>
#include <postgresql/libpq-fe.h>

class SqlWrapper {
public:
    SqlWrapper() : conn(PQconnectdb(get_config("config.txt").c_str())) {
        check_connect();
    }
    ~SqlWrapper() = default;

    PGconn *getConn();

    void disconnect();

    bool query(const std::string& query, PGresult** result, const std::string& comment = "");
    bool exec(const std::string& query, const std::string& comment = "");
    bool check_connect();

private:
    PGconn *conn;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
