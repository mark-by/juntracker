#include "student.h"

std::vector<Course> Student::get_courses() const {
    std::string query = "SELECT course_id FROM payment WHERE student_id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Course> res_courses;
    for (int i = 0; i < PQntuples(result); i++) {
        int c_id = atoi(PQgetvalue(result, i, 0));
        query = "SELECT * FROM course WHERE id=" + std::to_string(c_id) + ";";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        std::string c_name = std::string(PQgetvalue(result, 0, 1));
        int c_price = atoi(PQgetvalue(result, 0, 2));
        std::string c_start_date = PQgetvalue(result, 0, 3);
        std::string c_end_date = PQgetvalue(result, 0, 4);
        auto res_course = Course(c_id, c_name, c_price, postgres);
        res_courses.push_back(res_course);
    }
    return res_courses;
}

Visit Student::get_visit(int lesson_id, const boost::posix_time::ptime &date) const {
    std::string query = "SELECT * FROM visit WHERE lesson_id=" + std::to_string(lesson_id)
            + " and visit_date=" + date.zone_as_posix_string() + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int visit_id = atoi(PQgetvalue(result, 0, 0));
    int v_was_in_class = atoi(PQgetvalue(result, 0, 1));
    Visit res_visit(visit_id, v_was_in_class, postgres);
    return res_visit;
}

Student Student::get_student(int student_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "SELECT * FROM student WHERE id=" + std::to_string(student_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int s_age = atoi(PQgetvalue(result, 0, 3));
    auto res_student = Student(student_id, s_name, s_surname, s_age, postgres);
    return res_student;
}

int Student::save(const std::string name, const std::string& surname, int age) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::ostringstream s;
    std::string table_name = "student";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO student VALUES (" << std::to_string(count_rows + 1) << ", '"
      << name << "', '" << surname << "', "
      << std::to_string(age) << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Student::remove(int student_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "DELETE FROM student WHERE id=" + std::to_string(student_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

