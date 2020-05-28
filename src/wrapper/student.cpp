#include "student.h"
#include <utils.hpp>

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
    auto _postgres = connect();
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);

    std::string query = "SELECT * FROM visit WHERE lesson_id=" + std::to_string(lesson_id)
            + " and visit_date='" + converter.convert(boost::posix_time::second_clock::universal_time(), "") + "';";
    PGresult *result = nullptr;
    if (!_postgres.query(query, &result)) {
        throw std::exception();
    }
    if (!PQntuples(result)) {
        throw std::runtime_error("visit not found");
    }
    int visit_id = atoi(PQgetvalue(result, 0, 0));
    bool v_was_in_class = strcmp(PQgetvalue(result, 0, 3), "t") == 0;
    std::string str_v_date = std::string(PQgetvalue(result, 0, 4));
    boost::posix_time::ptime v_date = converter.convert(str_v_date);
    Visit res_visit(visit_id, v_was_in_class, v_date, postgres);
    return res_visit;
}

Student Student::get_student(int student_id) {
    auto postgres = connect();

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
    auto postgres = connect();

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
    auto postgres = connect();

    std::string query = "DELETE FROM student WHERE id=" + std::to_string(student_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

