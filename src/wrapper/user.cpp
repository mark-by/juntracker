#include "user.h"
#include <common_sql.hpp>

std::vector<Teacher> User::get_teachers() const {
    SqlWrapper postgres;
    std::ostringstream query;
    PGresult *result = nullptr;
    query << "select teacher.id, name, surname, age, salary, tel_number, description, avatar"
    << " from teacher join users on teacher.user_id=users.id where users.school_id=" << _school_id << ";";
    postgres.query(query.str(), &result, "Get lessons for weekday by user");

    std::vector<Teacher> teachers;
    teachers.reserve(PQntuples(result));
    for (int i = 0; i < PQntuples(result); i++) {
        teachers.emplace_back(std::stoi(PQgetvalue(result, i, 0)),
                              PQgetvalue(result, i, 1),
                              PQgetvalue(result, i, 2),
                              std::stoi(PQgetvalue(result, i, 3)),
                              std::stoi(PQgetvalue(result, i, 4)),
                              PQgetvalue(result, i, 5),
                              PQgetvalue(result, i, 6),
                              PQgetvalue(result, i, 7),

        );
    }
    postgres.disconnect();
    return teachers;
}



std::vector<Lesson> User::get_current_lessons() const {
    SqlWrapper postgres;
    boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
    int curr_weekday = d.day_of_week().as_number();
    std::ostringstream query;
    PGresult *result = nullptr;
    query << "SELECT * FROM lesson WHERE weekday='" << curr_weekday << "' and school_id=" << _school_id << ";";
    postgres.query(query.str(), &result, "Get lessons for weekday by user");

    std::vector<Lesson> res_lesson;
    res_lesson.reserve(PQntuples(result));
    for (int i = 0; i < PQntuples(result); i++) {
        res_lesson.emplace_back(std::stoi(PQgetvalue(result, i, 0)),
                                std::stoi(PQgetvalue(result, i, 2)),
                                curr_weekday,
                                PQgetvalue(result, i, 5),
                                PQgetvalue(result, i, 6));
    }
    postgres.disconnect();
    return res_lesson;
}

std::vector<Lesson> User::get_lessons_by_weekday(int l_weekday) const {
    SqlWrapper postgres;
    std::ostringstream query;
    PGresult *result = nullptr;
    query << "SELECT * FROM lesson WHERE weekday='" << l_weekday << "' and school_id=" << _school_id << ";";
    postgres.query(query.str(), &result, "Get lessons for weekday by user");
    std::vector<Lesson> res_lesson;
    res_lesson.reserve(PQntuples(result));
    for (int i = 0; i < PQntuples(result); i++) {
        res_lesson.emplace_back(atoi(PQgetvalue(result, i, 0)),
                                atoi(PQgetvalue(result, i, 2)),
                                l_weekday,
                                PQgetvalue(result, i, 5),
                                PQgetvalue(result, i, 6));
    }
    postgres.disconnect();
    return res_lesson;
}

std::vector<Student> User::get_students() const {
    SqlWrapper postgres;
    std::ostringstream query;
    PGresult *result = nullptr;
    query << "SELECT * FROM student WHERE school_id='" << _school_id << "';";
    postgres.query(query.str(), &result, "Get students");

    std::vector<Student> res_students;
    res_students.reserve(PQntuples(result));
    for (int i = 0; i < PQntuples(result); i++) {
        res_students.emplace_back(
                std::stoi(PQgetvalue(result, i, 0)),
                PQgetvalue(result, i, 1),
                PQgetvalue(result, i, 2),
                std::stoi(PQgetvalue(result, i, 3)),
                PQgetvalue(result, i, 5));
    }
    postgres.disconnect();
    return res_students;
}

User User::get_user(int user_id) {
    SqlWrapper postgres;
    std::ostringstream query;
    query << "SELECT * FROM users WHERE id=" << user_id << ";";

    PGresult *result = nullptr;
    postgres.query(query.str(), &result, "Get user by id");

    postgres.disconnect();
    return User(
            user_id,
            PQgetvalue(result, 0, 1),
            PQgetvalue(result, 0, 2),
            std::stoi(PQgetvalue(result, 0, 6)),
            PQgetvalue(result, 0, 3),
            std::stoi(PQgetvalue(result, 0, 4)),
            PQgetvalue(result, 0, 5));
}

int User::save(const std::string &username, const std::string &password, const std::string &email, int permission) {
    SqlWrapper postgres;
    std::ostringstream s;
    s << "INSERT INTO users(email, login, password, permission) VALUES ('" << email << "', '" << username << "', '"
      << password << "', " << permission << ");";

    postgres.exec(s.str(), "Save user");
    postgres.disconnect();
    return 0;
}

int User::remove(int user_id) {
    SqlWrapper postgres;
    std::ostringstream query;
    query << "DELETE FROM users WHERE id=" << user_id << ";";
    postgres.exec(query.str(), "Remove user");
    postgres.disconnect();
    return 0;
}

User User::get_user(const std::string &username) {
    SqlWrapper postgres;
    std::ostringstream query;
    query << "SELECT * FROM users WHERE login=" << username << ";";
    PGresult *result = nullptr;
    postgres.query(query.str(), &result, "Get user by username");

    postgres.disconnect();
    return User(
            std::stoi(PQgetvalue(result, 0, 0)),
            PQgetvalue(result, 0, 1),
            username,
            std::stoi(PQgetvalue(result, 0, 6)),
            PQgetvalue(result, 0, 3),
            std::stoi(PQgetvalue(result, 0, 4)),
            PQgetvalue(result, 0, 5));
}
