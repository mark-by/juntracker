#include "test.h"

TEST(DataBase, IsConnected) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    bool ok = postgres.is_connected();
    EXPECT_EQ(ok, true);
}

TEST(DataBase, CreateTable) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "CREATE TABLE student;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, CreateTable_2) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "CREATE TABLE teacher;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, CreateTable_3) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "CREATE TABLE course;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "INSERT INTO student VALUES(1, 'Boris', 'Petrov', 14);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_2) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
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
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "INSERT INTO course VALUES(1, 'playing piano', 15000, 'Smirnova', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_5) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "INSERT INTO course VALUES(2, 'python programming', 12000 'Demidov', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, UpdateValues) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    const std::string query = "UPDATE teacher SET salary = 14000 WHERE salary < 14000;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, SelectValues) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    ResultSet resultSet;
    const std::string query = "SELECT FROM student, WHERE id = 2;";
    bool ok = postgres.query(query, [](const ResultSet& resultSet){});
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"id", "name", "surname", "age"};
    std::vector<std::variant<std::string, int, double>> values = {2, "Anna", "Borisenko", 13};
    for (int col = 0; col < resultSet.get_cols(); col++) {
        auto column = resultSet.get(col);
        EXPECT_EQ(column.column_name, column_names[col]);
        EXPECT_EQ(column.value, values[col]);
    }
}

TEST(DataBase, SelectValues_2) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    ResultSet resultSet;
    const std::string query = "SELECT name, surname FROM teacher, WHERE id = 1;";
    bool ok = postgres.query(query, [](const ResultSet& resultSet){});
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"name", "surname",};
    std::vector<std::variant<std::string, int, double>> values = {"Olga", "Smirnova"};

    for (int col = 0; col < resultSet.get_cols(); col++) {
        auto column = resultSet.get(col);
        EXPECT_EQ(column.column_name, column_names[col]);
        EXPECT_EQ(column.value, values[col]);
    }
}

TEST(DataBase, SelectValues_3) {
    std::shared_ptr<PGConnection>  m_connection;
    SqlWrapper postgres(m_connection);
    ResultSet resultSet;
    const std::string query = "SELECT name, surname FROM student, WHERE id <= 2;";
    bool ok = postgres.query(query, [](const ResultSet& resultSet){});
    EXPECT_EQ(ok, true);
    std::vector<std::vector<std::variant<std::string, int, double>>> values = {{"Boris", "Petrov"}, {"Anna", "Borisenko"}};
    std::vector<std::string> column_names = {"name", "surname"};
    int count_rows = 0;

    while (resultSet.next()) {
        for (int col = 0; col < resultSet.get_cols(); col++) {
            auto column = resultSet.get(col);
            EXPECT_EQ(column.column_name, column_names[col]);
            EXPECT_EQ(column.value, values[count_rows][col]);
        }
        count_rows++;
    }
}
