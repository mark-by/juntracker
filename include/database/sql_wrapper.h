#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include <postgresql/libpq-fe.h>

#include <functional>
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

class ResultSet {
private:
    struct Value {
        enum Type { TEXT, INTEGER, DOUBLE, NULL_VALUE };
        Type type;
        std::string column_name;
        std::variant<std::string, int, double> value;
    };

    using Table = std::vector<std::vector<Value>>;
    mutable Table table;
    mutable std::vector<std::vector<Value>>::iterator tableIt{nullptr};

    size_t tRows{0};
    size_t tCols{0};

public:
    explicit ResultSet(size_t rows, size_t cols,
                       std::vector<std::pair<std::string, std::variant<std::string, int, double>>>& result);

    const Value get(size_t idx) const;
    size_t get_rows() const { return tRows; }
    size_t get_cols() const { return tCols; }
    bool next() const;
};

class SqlWrapper {
private:
    using HandlerFunc = std::function<void (const ResultSet&)>;
    std::shared_ptr<PGConnection> m_connection;

public:
    explicit SqlWrapper(std::shared_ptr<PGConnection> m_connection);
    ~SqlWrapper() = default;

    [[nodiscard]] bool is_select(const std::string& query) const;
    bool query(const std::string& query, const HandlerFunc& handler);
    bool exec(const std::string& query);
    [[nodiscard]] bool is_connected() const;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
