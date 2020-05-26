#include "lesson.h"

std::vector<Student> Lesson::get_students() const {
    std::string query = "SELECT student_id FROM visit WHERE lesson_id='" + std::to_string(id()) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<int> student_ids;
    for (int i = 0; i < PQntuples(result); i++) {
        student_ids.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<Student> res_students;
    for (auto s_id : student_ids) {
        query = "SELECT * FROM student WHERE id='" + std::to_string(s_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        std::string s_name = std::string(PQgetvalue(result, 0, 1));
        std::string s_surname = std::string(PQgetvalue(result, 0, 2));
        int s_age = atoi(PQgetvalue(result, 0, 3));
        Student curr_student(s_id, s_name, s_surname, s_age, postgres);
        res_students.push_back(curr_student);
    }

    return res_students;
}

Teacher Lesson::get_teacher() const {
    std::string query = "SELECT teacher_id FROM visit WHERE lesson_id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int t_id = atoi(PQgetvalue(result, 0, 0));

    query = "SELECT * FROM teacher WHERE id='" + std::to_string(t_id) + "';";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int t_salary = atoi(PQgetvalue(result, 0, 3));
    Teacher res_teacher(t_id, t_name, t_surname, t_salary,postgres);

    return res_teacher;
}

std::string Lesson::get_title() const {
    std::string query = "SELECT course_id FROM lesson WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int c_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT name FROM course WHERE id=" + std::to_string(c_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string c_name = std::string(PQgetvalue(result, 0, 1));
    return c_name;
}

Lesson Lesson::get_lesson(int lesson_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "SELECT * FROM lesson WHERE id=" + std::to_string(lesson_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int l_cabinet = atoi(PQgetvalue(result, 0, 2));
    int l_weekday = atoi(PQgetvalue(result, 0, 4));
    std::string l_start_time = std::string(PQgetvalue(result, 0, 5));
    std::string l_end_time = std::string(PQgetvalue(result, 0, 6));
    auto res_lesson = Lesson(lesson_id, l_cabinet, l_weekday, l_start_time, l_end_time, postgres);
    return res_lesson;
}

int Lesson::save(int cabinet, const std::string& weekday, const std::string& start, const std::string& end) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::ostringstream s;
    std::string table_name = "lesson";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO lesson VALUES (" << std::to_string(count_rows + 1) << ", "
      << std::to_string(cabinet) << ", '" << weekday << "', '"
      << start << "', '" << end << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Lesson::remove(int lesson_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "DELETE FROM lesson WHERE id=" + std::to_string(lesson_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}



