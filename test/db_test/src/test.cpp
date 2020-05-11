#include "gtest/gtest.h"
#include "sql_wrapper.h"
#include <string>

const char* conninfo = "host=localhost port=5432 dbname=jun_tracker user=amavrin password=root";
PGconn *conn = PQconnectdb(conninfo);
SqlWrapper postgres(conn);

TEST(DataBase, IsConnected) {
    bool ok = postgres.is_connected();
    EXPECT_EQ(ok, true);
}

TEST(DataBase, CreateTable) {
    const std::string query = "CREATE TABLE student;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, CreateTable_2) {
    const std::string query = "CREATE TABLE teacher;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, CreateTable_3) {
    const std::string query = "CREATE TABLE course;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable) {
    const std::string query = "INSERT INTO student VALUES(1, 'Boris', 'Petrov', 14);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_2) {
    std::shared_ptr<PGConnection>  m_connection;
    const std::string query = "INSERT INTO student VALUES(2, 'Anna', 'Borisenko', 13);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_3) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "INSERT INTO teacher VALUES(1, 'Olga', 'Smirnova', 12000, 'playing piano');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_4) {
    const std::string query = "INSERT INTO course VALUES(1, 'playing piano', 15000, 'Smirnova', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_5) {
    const std::string query = "INSERT INTO course VALUES(2, 'python programming', 12000 'Demidov', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, UpdateValues) {
    const std::string query = "UPDATE teacher SET salary = 14000 WHERE salary < 14000;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, SelectValues) {
    const std::string query = "SELECT FROM student, WHERE id = 3;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"id", "name", "surname", "age", "course_id"};
    std::vector<std::variant<std::string, int, double>> values = {3, "Anna", "Borisenko", 12, 1};
    for (int col = 0; col < PQnfields(result); col++) {
        EXPECT_EQ(PQfname(result, col), column_names[col]);
        EXPECT_EQ(PQgetvalue(result, 0, col), values[col]);
    }
}

TEST(DataBase, SelectValues_2) {
    const std::string query = "SELECT name, surname FROM teacher, WHERE id = 1;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"name", "surname",};
    std::vector<std::variant<std::string, int, double>> values = {"Olga", "Smirnova"};
    for (int col = 0; col < PQnfields(result); col++) {
        EXPECT_EQ(PQfname(result, col), column_names[col]);
        EXPECT_EQ(PQgetvalue(result, 0, col), values[col]);
    }
}

TEST(DataBase, SelectValues_3) {
    const std::string query = "SELECT name, surname FROM student, WHERE id <= 2;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::vector<std::vector<std::variant<std::string, int, double>>> values = {{"Matvey", "Kuzmenko"}, {"Kuzma", "Matveenko"}};
    std::vector<std::string> column_names = {"name", "surname"};
    for (int row = 0; row < PQntuples(result); row++) {
        for (int col = 0; col < PQnfields(result); col++) {
            EXPECT_EQ(PQfname(result, col), column_names[col]);
            EXPECT_EQ(PQgetvalue(result, row, col), values[col]);
        }
    }
}
