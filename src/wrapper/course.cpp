#include "course.h"

Teacher Course::get_teacher(const std::string& course_name) const {
    std::string query = "SELECT teacher_id FROM course WHERE name='" + course_name + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    int teacher_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    query = "SELECT * FROM teacher WHERE id=" + std::to_string(teacher_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int salary = atoi(PQgetvalue(result, 0, 3));
    std::string description = PQgetvalue(result, 0, 4);
    auto res_teacher = Teacher(teacher_id, t_name, t_surname, salary, description);
    PQclear(result);

    return res_teacher;
}

int Course::get_price(const std::string& course_name) const {
    std::string query = "SELECT price FROM course WHERE name='" + course_name + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int c_price = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    return c_price;
}

int Course::set_price(int c_price, const std::string& course_name) {
    std::string query = "UPDATE course SET price=" + std::to_string(c_price)  + " WHERE name='" + course_name + "';";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

std::vector<Student> Course::get_student_list(const std::string& course_name) const {

    std::string query = "SELECT id FROM course WHERE name='" + course_name + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int course_id = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);

    query = "SELECT * FROM payment WHERE course_id=" + std::to_string(course_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Student> students;
    for (int i = 0; i < PQntuples(result); i++) {
        int s_id = atoi(PQgetvalue(result, i, 0));
        std::string s_name = std::string(PQgetvalue(result, i, 1));
        std::string s_surname = std::string(PQgetvalue(result, i, 2));
        int s_age = atoi(PQgetvalue(result, i, 3));
        auto res_student = Student(s_id, s_name, s_surname, s_age);
        students.push_back(res_student);
    }
    PQclear(result);
    return students;
}

std::vector<Course> Course::get_courses_by_teacher(int t_id) {
    std::string query = "SELECT * FROM course WHERE id='" + std::to_string(t_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    std::vector<Course> courses;
    for (int i = 0; i < PQntuples(result); i++) {
        int c_id = atoi(PQgetvalue(result, i, 0));
        std::string c_name = std::string(PQgetvalue(result, i, 1));
        int c_price = atoi(PQgetvalue(result, i, 2));
        std::string c_start_date = std::string(PQgetvalue(result, i, 3));
        std::string c_end_date = std::string(PQgetvalue(result, i, 4));
        auto res_course = Course(c_id, c_name, c_price,c_start_date, c_end_date);
        courses.push_back(res_course);
    }
    return courses;
}

Course Course::get_course(int c_id) const {
    std::string query = "SELECT * FROM course WHERE id=" + std::to_string(c_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string c_name = std::string(PQgetvalue(result, 0, 1));
    int c_price = atoi(PQgetvalue(result, 0, 2));
    std::string c_start_date = PQgetvalue(result, 0, 3);
    std::string c_end_date = PQgetvalue(result, 0, 4);
    auto res_course = Course(c_id, c_name, c_price, c_start_date, c_end_date);
    return res_course;
}

int Course::add_course(const Course& course) const {
    std::ostringstream s;
    s << "INSERT INTO course VALUES (" << std::to_string(course.id) << ", '"
      << course.name << "', " << std::to_string(course.price) << ", '"
      << course.start_date << "', '" << course.end_date << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Course::delete_course(int c_id) const {
    std::string query = "DELETE * FROM course WHERE id=" + std::to_string(c_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}
