#include "test.h"

TEST(DataBase IsConnected) {
    bool ok = postgres.is_connected();
    EXPECT_EQ(ok, true);
}

TEST(DataBase CreateTable) {
    const std::string query = "CREATE TABLE student;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase CreateTable) {
    const std::string query = "CREATE TABLE teacher;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase CreateTable) {
    const std::string query = "CREATE TABLE course;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase InsertTable) {
    const std::string query = "INSERT INTO student VALUES(1, 'Boris', 'Petrov', 14);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase InsertTable) {
    const std::string query = "INSERT INTO student VALUES(2, 'Anna', 'Borisenko', 13);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase InsertTable) {
    const std::string query = "INSERT INTO teacher VALUES(1, 'Olga', 'Smirnova', 12000, 'playing piano');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase InsertTable) {
    const std::string query = "INSERT INTO course VALUES(1, 'playing piano', 15000, 'Smirnova', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase InsertTable) {
    const std::string query = "INSERT INTO course VALUES(2, 'python programming', 12000 'Demidov', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase UpdateValues) {
    const std::string query = "UPDATE teacher SET salary = 14000 WHERE salary < 14000;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase SelectValues) {
    const std::string query = "SELECT FROM student, WHERE id = 2;";
    bool ok = postgres.exec(query, resultSet);
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"id", "name", "surname", "age"};
    std::vector<std::variant<std::string, int, double>> values = {2, 'Anna', 'Borisenko', 13};
    for (int col = 0; col < resultSet.get_cols(); col++) {
        auto column = resultSet.get(col = 1);
        EXPECT_EQ(column.get_column_name(), column_names[i]);
        EXPECT_EQ(column.get_value(), values[i]);
    }
}
