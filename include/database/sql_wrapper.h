#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include "abstract_db.h"

#include <iostream>
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

    bool query(const std::string& query, PGresult** result) const override;
    [[nodiscard]] bool exec(const std::string& query) const override;
    [[nodiscard]] bool is_connected() const override;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
