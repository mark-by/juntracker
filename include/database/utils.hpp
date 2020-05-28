#ifndef JUNTRACKER_UTILS_HPP
#define JUNTRACKER_UTILS_HPP
#include <string>
#include <sql_wrapper.h>

inline std::string get_config(const std::string & filename = "config.txt") {
    std::ifstream fin(filename);
    std::string conninfo;
    char ch;
    while (fin.get(ch)) {
        conninfo.push_back(ch);
    }
    fin.close();
    return conninfo;
}


inline SqlWrapper connect(const std::string &config_filename = "config.txt") {
    PGconn *conn = PQconnectdb(get_config(config_filename).c_str());
    return SqlWrapper(conn);
}

#endif //JUNTRACKER_UTILS_HPP
