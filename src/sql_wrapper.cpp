#include "sql_wrapper.h"

// PGConnection is ...
PGConnection::PGConnection() {
    // ToDo ctr
}

std::shared_ptr<PGconn> PGConnection::connection() const {
    return m_connection;
}

// ResultSet is ...
ResultSet::ResultSet(size_t rows, size_t cols,
                     std::vector<std::pair<std::string, std::variant<std::string, int, double>>>& result)
        : tRows(rows)
        , tCols(cols) {}

const ResultSet::Value ResultSet::get(size_t idx) const {
    // ToDo
}

bool ResultSet::next() const {
    // ToDo
    return true;
}

// SqlWrapper is ...
SqlWrapper::SqlWrapper(std::shared_ptr<PGConnection> m_connection) {
    // ToDo ctr
}

bool SqlWrapper::query(const std::string& query, const HandlerFunc& handler) {
    // ToDo
    return true;
}

bool SqlWrapper::exec(const std::string& query) {
    // ToDo
    return true;
}

bool SqlWrapper::is_connected() const {
    // ToDo
    return true;
}

bool SqlWrapper::is_select(const std::string& query) const {
    // ToDo
    return true;
}
