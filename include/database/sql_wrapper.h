#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include <postgresql/libpq-fe.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class SqlWrapper {
private:
    PGconn *conn;

public:
    explicit SqlWrapper() {}
    explicit SqlWrapper(PGconn *conn);
    ~SqlWrapper();

    [[nodiscard]] bool is_select(const std::string& query) const;
    bool query(const std::string& query, PGresult** result) const ;
    [[nodiscard]] bool exec(const std::string& query) const;
    [[nodiscard]] bool is_connected() const;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
