#include "visit.h"
#include <utils.hpp>

Student Visit::get_student() const {
    std::string query = "SELECT student_id FROM visit WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int student_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM student WHERE id=" + std::to_string(student_id) + ";";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int age = atoi(PQgetvalue(result, 0, 3));
    auto res_student = Student(student_id, s_name, s_surname, age, postgres);
    return res_student;
}

Lesson Visit::get_lesson() const {
    std::string query = "SELECT lesson_id FROM visit WHERE id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int lesson_id = atoi(PQgetvalue(result, 0, 0));
    query = "SELECT * FROM lesson WHERE id=" + std::to_string(lesson_id) + ";";
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

//Visit Visit::get_visit(int visit_id) {
//    auto postgres = connect();
//    const std::string format = "%a, %d %b %Y %H:%M:%S";
//    DateTimeConverter converter(format);
//
//    std::string query = "SELECT * FROM visit WHERE id=" + std::to_string(visit_id) + ";";
//    PGresult *result = nullptr;
//    if (!postgres.query(query, &result)) {
//        throw std::exception();
//    }
//    int v_was_in_class = atoi(PQgetvalue(result, 0, 1));
//    std::string str_v_date = std::string(PQgetvalue(result, 0, 2));
//    boost::posix_time::ptime v_date = converter.convert(str_v_date);
//    auto res_visit = Visit(visit_id, v_was_in_class, v_date, postgres);
//    return res_visit;
//}

int Visit::save(int student_id, int lesson_id, bool was_in_class) {
    auto postgres = connect();

    std::ostringstream s;
    std::string table_name = "visit";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO visit VALUES (" << std::to_string(count_rows + 1) << ", "
      << std::to_string(student_id) << ", " << std::to_string(lesson_id) << ", "
      << std::to_string(was_in_class)  << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        std::cout << "FAIL SAVE" << std::endl;
        return -1;
    }
    return 0;
}

int Visit::remove(int visit_id) {
    auto postgres = connect();

    std::string query = "DELETE FROM visit WHERE id=" + std::to_string(visit_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

