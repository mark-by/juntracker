#include "visit.h"
#include <utils.hpp>

Student Visit::get_student() const {
    SqlWrapper db;

    db << "SELECT student.id, student.name, student.surname, student.age, student.description FROM student "
       << "join visit on visit.student_id=student.id where visit.id" << _id << ";";
    db.query("Get student by visit id");
    db.disconnect();

    return Student(
            db.get_int(0, 0),
            db.get_str(1, 0),
            db.get_str(2, 0),
            db.get_int(3, 0),
            db.get_str(4, 0)
    );
}

Lesson Visit::get_lesson() const {
    SqlWrapper db;

    db << "SELECT lesson.id, lesson.course_id, lesson.cabinet_id, lesson.teacher_id, lesson.weekday, lesson.start_time, lesson.end_time FROM lesson"
       << "join visit on visit.lesson_id=lesson.id where visit.id=" << _id << ";";
    db.query("Get student by visit id");
    db.disconnect();

    return Lesson(
            db.get_int(0, 0),
            db.get_int(1, 0),
            db.get_int(2, 0),
            db.get_str(3, 0),
            db.get_str(4, 0)
    );
}

Visit Visit::get_visit(int visit_id) {
    SqlWrapper postgres;
    const std::string format = "%a, %d %b %Y %H:%M:%S";
    DateTimeConverter converter(format);

    std::string query = "SELECT * FROM visit WHERE id=" + std::to_string(visit_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    int v_was_in_class = atoi(PQgetvalue(result, 0, 1));
    std::string str_v_date = std::string(PQgetvalue(result, 0, 2));
    boost::posix_time::ptime v_date = converter.convert(str_v_date);
    postgres.disconnect();
    return Visit(visit_id, v_was_in_class, v_date);
}

int Visit::save(int student_id, int lesson_id, bool was_in_class) {
    SqlWrapper postgres;
    const std::string format = "%Y-%m-%d";
    DateTimeConverter converter(format);
    std::ostringstream s;
    std::string table_name = "visit";
    auto today = converter.convert(boost::posix_time::second_clock::universal_time(), "");
    PGresult *result = nullptr;
    char was_in_class_ch = (was_in_class ? 't' : 'f');
    s << "select count(*) from visit where student_id=" << student_id << " and lesson_id=" << lesson_id <<
    " and visit_date='" << today << "';";
    if (!postgres.query(s.str(), &result)) {
        std::cout << "FAIL SELECT" << std::endl;
        postgres.disconnect();
        return -1;
    }
    std::cout << "PQ: " << PQgetvalue(result, 0, 0) << std::endl;
    if (atoi(PQgetvalue(result, 0, 0))) {
        s.str("");
        s << "update visit set was_in_class='" << was_in_class_ch << "' where student_id=" << student_id <<
        " and lesson_id=" << lesson_id << " and visit_date='" << today << "';";
    } else {
        s.str("");
        int count_rows = postgres.count_rows(table_name);
        s << "INSERT INTO visit VALUES (" << std::to_string(count_rows + 1) << ", "
          << student_id << ", " << lesson_id << ", '"
          <<  was_in_class_ch << "', '" << today << "');";
    }

    std::string query = s.str();
    std::cout << query << std::endl;
    if (!postgres.exec(query)) {
        postgres.disconnect();
        std::cout << "FAIL SAVE" << std::endl;
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int Visit::remove(int visit_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM visit WHERE id=" + std::to_string(visit_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

