#ifndef ABSTRACT_DB_H_
#define ABSTRACT_DB_H_

#include <string>
#include <postgresql/libpq-fe.h>

class Database {
    virtual bool query(const std::string& query, PGresult** result) const = 0;
    [[nodiscard]] virtual bool exec(const std::string& query) const = 0;
    [[nodiscard]] virtual bool is_connected() const = 0;
};

#endif  // ABSTRACT_DB_H_
