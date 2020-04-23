#ifndef PROJECT_TESTS_INCLUDE_TEST_H_
#define PROJECT_TESTS_INCLUDE_TEST_H_

#include "gtest/gtest.h"
#include "sql_wrapper.h"
#include <string>

class ValueTest {
public:
    std::string get_column_name() { return column_name; }
    std::variant<std::string, int, double> get_value() { return value; }
 private:
    enum Type { TEXT, INTEGER, DOUBLE, NULL_VALUE };
    Type type;
    std::string columnName;
    std::variant<std::string, int, double> value;
};

#endif  // PROJECT_TESTS_INCLUDE_TEST_H_
