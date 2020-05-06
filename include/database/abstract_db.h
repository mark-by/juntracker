#ifndef ABSTRACT_DB_H_
#define ABSTRACT_DB_H_

#include <string>

class Database {
    virtual bool is_select(const std::string& query) const = 0;
    virtual bool query(const std::string& query, const HandlerFunc& handler) = 0;
    virtual bool exec(const std::string& query) = 0;
    virtual bool is_connected() const = 0;
};

#endif  // ABSTRACT_DB_H_
