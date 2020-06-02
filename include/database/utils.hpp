#ifndef JUNTRACKER_UTILS_HPP
#define JUNTRACKER_UTILS_HPP

#include <string>
#include <postgresql/libpq-fe.h>
#include <random>
#include <regex>

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

inline std::string randomStr(int len) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::string alphanum =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<int> distribution(1,alphanum.size());

    std::string str;
    for (int i = 0; i < len; ++i) {
        str.push_back(alphanum[distribution(generator) % (alphanum.size() - 1)]);
    }
    return str;
}

inline std::pair<std::string, std::string> parse_name_surname(const std::string& str) {
    std::regex tag(R"((\w+)\s*([\w+]*))");
    std::sregex_iterator match(str.begin(), str.end(), tag);
    return {match->format("$1"), match->format("$2")};
}

#endif //JUNTRACKER_UTILS_HPP
