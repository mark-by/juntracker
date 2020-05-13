#include "gtest/gtest.h"
#include "sql_wrapper.h"
#include "course.h"
#include "teacher.h"
#include "student.h"

#include <string>

const char* conninfo = "host=localhost port=5432 dbname=jun_tracker user=amavrin password=root";
PGconn *conn = PQconnectdb(conninfo);
SqlWrapper postgres(conn);

TEST(DataBase, IsConnected) {
    bool ok = postgres.is_connected();
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable) {
    const std::string query = "INSERT INTO student VALUES(1, 'Boris', 'Petrov', 14);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_2) {
    const std::string query = "INSERT INTO student VALUES(2, 'Anna', 'Borisenko', 13);";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, InsertTable_3) {
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
    const std::string query = "INSERT INTO course VALUES(2, 'python programming', 12000 'Tokarev', '01.02', '31.05');";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, UpdateValues) {
    const std::string query = "UPDATE teacher SET salary = 14000 WHERE salary < 14000;";
    bool ok = postgres.exec(query);
    EXPECT_EQ(ok, true);
}

TEST(DataBase, SelectValues) {
    const std::string query = "SELECT * FROM student WHERE id = 3;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"id", "name", "surname", "age", "course_id"};
    std::vector<std::string> values = {"3", "Anna", "Borisenko", "12", "1"};
    for (int col = 0; col < PQnfields(result); col++) {
        EXPECT_EQ(PQfname(result, col), column_names[col]);
        EXPECT_EQ(PQgetvalue(result, 0, col), values[col]);
    }
}

TEST(DataBase, SelectValues_2) {
    const std::string query = "SELECT name, surname FROM teacher WHERE id = 1;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::vector<std::string> column_names = {"name", "surname",};
    std::vector<std::string> values = {"Olga", "Smirnova"};
    for (int col = 0; col < PQnfields(result); col++) {
        EXPECT_EQ(PQfname(result, col), column_names[col]);
        EXPECT_EQ(PQgetvalue(result, 0, col), values[col]);
    }
}

TEST(DataBase, SelectValues_3) {
    const std::string query = "SELECT name, surname FROM student WHERE id <= 2;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::vector<std::vector<std::string>> values = {{"Matvey", "Kuzmenko"}, {"Kuzma", "Matveenko"}};
    std::vector<std::string> column_names = {"name", "surname"};
    for (int row = 0; row < PQntuples(result); row++) {
        for (int col = 0; col < PQnfields(result); col++) {
            EXPECT_EQ(PQfname(result, col), column_names[col]);
            EXPECT_EQ(PQgetvalue(result, row, col), values[row][col]);
        }
    }
}

TEST(DataBase, SelectValues4) {
    const std::string query = "SELECT name FROM course WHERE price = 12000;";
    PGresult *result = nullptr;
    bool ok = postgres.query(query, &result);
    EXPECT_EQ(ok, true);
    std::string column_name = "name";
    std::vector<std::string> values = {"python programming", "drawing"};
    for (int row = 0; row < PQntuples(result); row++) {
        EXPECT_EQ(PQfname(result, 0), column_name);
        EXPECT_EQ(PQgetvalue(result, row, 0), values[row]);
    }
}

TEST(DataBase, CourseTest) {
    const std::string course_name = "sambo";
    Course course(postgres);
    int c_amount = course.get_price(course_name);
    EXPECT_EQ(c_amount, 10000);
}

TEST(DataBase, CourseTest2) {
    int c_id = 5;
    Course course(postgres);
    std::string c_name = "chess";
    int c_price = 10000;
    std::string c_start_date = "2020-02-01";
    std::string c_end_date = "2020-05-31";
    Course course_add(c_id, c_name, c_price, c_start_date, c_end_date);
    int insertion = course.add_course(course_add);
    EXPECT_EQ(insertion, 0);
    int deletion = course.delete_course(c_id);
    EXPECT_EQ(deletion, 0);
}

TEST(DataBase, TeacherTest) {
    const int t_id = 2;
    Teacher teacher(postgres);
    std::string c_name = teacher.get_course(t_id);
    EXPECT_EQ(c_name, "python programming");
}

TEST(DataBase, TeacherTest2) {
    int t_id = 2;
    Teacher teacher(postgres);
    std::string t_name = "Pavel";
    std::string t_surname = "Alexandrov";
    int t_salary = 13000;
    std::string t_description = "chess";
    Teacher teacher_add(t_id, t_name, t_surname, t_salary, t_description);
    int insertion = teacher.add_teacher(teacher_add);
    EXPECT_EQ(insertion, 0);
    int deletion = teacher.delete_teacher(t_id);
    EXPECT_EQ(deletion, 0);
}

TEST(DataBase, StudentTest) {
    const int s_id = 6;
    Student student(postgres);
    std::string s_course = student.get_course(s_id);
    EXPECT_EQ(s_course, "python programming");
}

TEST(DataBase, StudentTest2) {
    int s_id = 11;
    Student student(postgres);
    std::string s_name = "Victor";
    std::string s_surname = "Voronin";
    int s_age = 14;
    std::string s_description = "sambo";
    Student student_add(s_id, s_name, s_surname, s_age, s_description);
    int insertion = student.add_student(student_add);
    EXPECT_EQ(insertion, 0);
    int deletion = student.delete_student(s_id);
    EXPECT_EQ(deletion, 0);
}
