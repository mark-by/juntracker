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

class SqlWrapper : public Database {
private:
    PGconn *conn;

public:
    explicit SqlWrapper() {}
    explicit SqlWrapper(PGconn *conn);
    ~SqlWrapper() = default;

    PGconn *getConn();

    bool query(const std::string& query, PGresult** result) const override;
    [[nodiscard]] bool exec(const std::string& query) const override;
    [[nodiscard]] bool is_connected() const override;
    int count_rows(std::string& table_name) const;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
