#include <iostream>
#include "sql_wrapper.h"

int main(int argc, char* argv[]) {

    const std::string query = "SQL REQUEST";

    // Create Connection
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);

    // Check Connection
    if (!postgres.is_connected()) {
        return 1;
    }

    // Create Data storage object
    using HandlerFunc = std::function<void (const ResultSet&)>;
    const HandlerFunc handler;

    if (postgres.is_select(query)) {
        postgres.query(query, handler);
    } else {
        postgres.exec(query);
    }

    std::cout << "It compiles" << std::endl;
    return 0;
}
