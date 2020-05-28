#include "teacher.h"
#include <utils.hpp>

std::vector<Course> Teacher::get_courses() const {
    SqlWrapper postgres;
    std::string query = "SELECT * FROM course WHERE teacher_id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }

    std::vector<Course> courses;
    for (int i = 0; i < PQntuples(result); i++) {
        int c_id = atoi(PQgetvalue(result, i, 0));
        std::string c_name = std::string(PQgetvalue(result, i, 1));
        int c_price = atoi(PQgetvalue(result, i, 2));
        std::string c_start_date = std::string(PQgetvalue(result, i, 3));
        std::string c_end_date = std::string(PQgetvalue(result, i, 4));
        auto res_course = Course(c_id, c_name, c_price);
        courses.push_back(res_course);
    }
    postgres.disconnect();
    return courses;
}

Teacher Teacher::get_teacher(int teacher_id) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM teacher WHERE id=" + std::to_string(teacher_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int t_salary = atoi(PQgetvalue(result, 0, 3));
    postgres.disconnect();
    return Teacher(teacher_id, t_name, t_surname, t_salary);
}

int Teacher::save(const std::string& name, const std::string& surname, int salary) {
    SqlWrapper postgres;

    std::ostringstream s;
    std::string table_name = "teacher";
    int count_rows = postgres.count_rows(table_name);

    s << "INSERT INTO teacher VALUES (" << std::to_string(count_rows + 1) << ", '"
      << name << "', '" << surname << "', " << std::to_string(salary) << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int Teacher::remove(int teacher_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM teacher WHERE id=" + std::to_string(teacher_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}