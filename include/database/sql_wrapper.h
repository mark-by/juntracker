#ifndef PROJECT_INCLUDE_SQL_WRAPPER_H_
#define PROJECT_INCLUDE_SQL_WRAPPER_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <utils.hpp>
#include <postgresql/libpq-fe.h>
#include <memory>

class SqlWrapper {
public:
    SqlWrapper() : conn(PQconnectdb(get_config("config.txt").c_str())), os(""), result(nullptr){
        check_connect();
    }
    ~SqlWrapper() = default;

    template<class Value>
    std::ostream &operator<<(const Value &value) {
        os << value;
        return os;
    }

    void clear();

    PGconn *getConn();

    void disconnect();

    bool query(const std::string& comment = "");
    bool exec(const std::string& comment = "");
    char * get_str(int field_num, int tup_num = 0);
    int get_int(int field_num, int tup_num = 0);
    bool get_bool(int field_num, int tup_num = 0);
    int count_tupls();
    bool check_connect();

private:
   PGconn *conn;
    std::ostringstream os;
    PGresult *result;
};

#endif  // PROJECT_INCLUDE_SQL_WRAPPER_H_
