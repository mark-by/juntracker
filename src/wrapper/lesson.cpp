#include "lesson.h"
#include "utils.hpp"

std::vector<Student> Lesson::get_students() const {
    SqlWrapper db;
    db << "SELECT student_id FROM students_for_lesson WHERE lesson_id=" << _id << ";";
    db.query("Get students id on lesson");
    std::vector<int> student_ids;
    for (int i = 0; i < PQntuples(result); i++) {
        student_ids.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<Student> res_students;
    for (auto s_id : student_ids) {
        query = "SELECT * FROM student WHERE id='" + std::to_string(s_id) + "';";
        if (!postgres.query(query, &result)) {
            postgres.disconnect();
            throw std::exception();
        }
        std::string s_name = std::string(PQgetvalue(result, 0, 1));
        std::string s_surname = std::string(PQgetvalue(result, 0, 2));
        int s_age = atoi(PQgetvalue(result, 0, 3));
        Student curr_student(s_id, s_name, s_surname, s_age);
        res_students.push_back(curr_student);
    }

    postgres.disconnect();
    return res_students;
}

Teacher Lesson::get_teacher() const {
    SqlWrapper postgres;
    std::string query = "SELECT teacher_id FROM lesson WHERE id=" + std::to_string(_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int t_id = atoi(PQgetvalue(result, 0, 0));

    query = "SELECT * FROM teacher WHERE id='" + std::to_string(t_id) + "';";
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int t_salary = atoi(PQgetvalue(result, 0, 3));
    postgres.disconnect();
    return Teacher (t_id, t_name, t_surname, t_salary);
}

std::string Lesson::get_title() const {
    SqlWrapper postgres;
    std::string query = "SELECT course_id FROM lesson WHERE id=" + std::to_string(_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int c_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT name FROM course WHERE id=" + std::to_string(c_id) + ";";
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string c_name = std::string(PQgetvalue(result, 0, 0));
    postgres.disconnect();
    return c_name;
}

Lesson Lesson::get_lesson(int lesson_id) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM lesson WHERE id=" + std::to_string(lesson_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int l_cabinet = atoi(PQgetvalue(result, 0, 2));
    int l_weekday = atoi(PQgetvalue(result, 0, 4));
    std::string l_start_time = std::string(PQgetvalue(result, 0, 5));
    std::string l_end_time = std::string(PQgetvalue(result, 0, 6));
    postgres.disconnect();
    return Lesson(lesson_id, l_cabinet, l_weekday, l_start_time, l_end_time);
}

int Lesson::save(int _course_id, int _cabinet_id, int _teacher_id, int _weekday,
        const std::string& _start_time, const std::string& _end_time, int _school_id) {
    SqlWrapper postgres;

    std::ostringstream s;
    std::string table_name = "lesson";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO lesson VALUES (" << std::to_string(count_rows + 1) << ", "
      << std::to_string(cabinet) << ", '" << weekday << "', '"
      << start << "', '" << end << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int Lesson::remove(int lesson_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM lesson WHERE id=" + std::to_string(lesson_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}



