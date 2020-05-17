#include "student.h"

std::string Student::get_name(int s_id) const {
    std::string query = "SELECT name FROM student WHERE id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = PQgetvalue(result, 0, 0);
    PQclear(result);
    return t_name;
}

std::string Student::get_surname(int s_id) const {
    std::string query = "SELECT surname FROM student WHERE id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string s_surname = PQgetvalue(result, 0, 0);
    PQclear(result);
    return s_surname;
}

int Student::get_age(int s_id) const {
    std::string query = "SELECT age FROM student WHERE id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int s_age = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return s_age;
}

std::string Student::get_course(int s_id) const {
    std::string query = "SELECT course_id FROM payment WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string c_id = PQgetvalue(result, 0, 0);
    query = "SELECT name FROM course WHERE id=" + c_id + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string c_name = PQgetvalue(result, 0, 0);
    return c_name;
}

Student Student::get_student(int s_id) const {
    std::string query = "SELECT * FROM student WHERE id=" + std::to_string(id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int s_age = atoi(PQgetvalue(result, 0, 3));
    auto res_student = Student(s_id, s_name, s_surname, s_age);
    return res_student;
}

int Student::add_student(const Student& student) const {
    std::ostringstream s;
    s << "INSERT INTO student VALUES (" << std::to_string(student.id) << ", "
      << student.name << ", " << student.surname << ", "
      << std::to_string(student.age) << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Student::delete_student(int s_id) const {
    std::string query = "DELETE * FROM student WHERE id=" + std::to_string(s_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

