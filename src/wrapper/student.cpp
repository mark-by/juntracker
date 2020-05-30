#include "student.h"
#include <utils.hpp>

std::vector<Course> Student::get_courses() const {
//    SqlWrapper db;
//    db << "SELECT course_id FROM payment WHERE student_id='" << _id << "';";
//    db.query("Get courses by student");
//    std::vector<Course> res_courses;
//    for (int i = 0; i < db.count_tupls(); i++) {
//        int c_id = atoi(PQgetvalue(result, i, 0));
//        query = "SELECT * FROM course WHERE id=" + std::to_string(c_id) + ";";
//        if (!db.query(query, &result)) {
//            db.disconnect();
//            throw std::exception();
//        }
//        std::string c_name = std::string(PQgetvalue(result, 0, 1));
//        int c_price = atoi(PQgetvalue(result, 0, 2));
//        std::string c_start_date = PQgetvalue(result, 0, 3);
//        std::string c_end_date = PQgetvalue(result, 0, 4);
//        auto res_course = Course(c_id, c_name, c_price);
//        res_courses.push_back(res_course);
//    }
//    db.disconnect();
//МИША, МНЕ КАЖЕТСЯ, ТУТ НУЖНЫ ТВОИ JOIN
//    return res_courses;
}

Visit Student::get_visit(int lesson_id, const boost::posix_time::ptime &date) const {
    SqlWrapper db;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);
    db << "SELECT * FROM visit WHERE lesson_id=" << std::to_string(lesson_id) << " and visit_date='"
    << converter.convert(boost::posix_time::second_clock::universal_time(), "") << "' and student_id=" << _id << ";";
    db.query("Get visit by student");
    db.disconnect();
    boost::posix_time::ptime v_date = converter.convert(db.get_str(4));
    return Visit(db.get_int(0), db.get_bool(3), v_date);
}

Student Student::get_student(int student_id) {
    SqlWrapper db;

    std::string query = "SELECT * FROM student WHERE id=" + std::to_string(student_id) + ";";
    PGresult *result = nullptr;
    if (!db.query(query, &result)) {
        db.disconnect();
        throw std::exception();
    }
    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int s_age = atoi(PQgetvalue(result, 0, 3));
    auto res_student = Student(student_id, s_name, s_surname, s_age);
    db.disconnect();
    return res_student;
}

int Student::save(const std::string name, const std::string& surname, int age) {
    SqlWrapper db;

    std::ostringstream s;
    std::string table_name = "student";
    int count_rows = db.count_rows(table_name);
    s << "INSERT INTO student VALUES (" << std::to_string(count_rows + 1) << ", '"
      << name << "', '" << surname << "', "
      << std::to_string(age) << ");";

    std::string query = s.str();
    if (!db.exec(query)) {
        db.disconnect();
        return -1;
    }
    db.disconnect();
    return 0;
}

int Student::remove(int student_id) {
    SqlWrapper db;

    std::string query = "DELETE FROM student WHERE id=" + std::to_string(student_id) + ";";
    if (!db.exec(query)) {
        db.disconnect();
        return -1;
    }
    db.disconnect();
    return 0;
}

