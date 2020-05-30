#ifndef JUNTRACKER_UTILS_HPP
#define JUNTRACKER_UTILS_HPP

#include <string>
#include <postgresql/libpq-fe.h>

inline std::string get_config(const std::string &filename = "config.txt") {
    std::ifstream fin(filename);
    std::string conninfo;
    char ch;
    while (fin.get(ch)) {
        conninfo.push_back(ch);
    }
    fin.close();
    return conninfo;
}

#endif //JUNTRACKER_UTILS_HPP
