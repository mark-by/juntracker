#include "user.h"
#include <common_sql.hpp>

std::vector<Teacher> User::get_teachers() const {
    SqlWrapper db;
    db << "select teacher.id, name, age, surname, salary, tel_number, description, avatar"
       << " from teacher join users on teacher.user_id=users.id where users.school_id=" << _school_id << ";";
    db.query("Get teachers");

    std::vector<Teacher> teachers;
    teachers.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        teachers.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_int(2, i),
                db.get_str(3, i),
                db.get_int(4, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_str(7, i)
        );
    }
    db.disconnect();
    return teachers;
}

std::vector<Lesson> User::get_current_lessons() const {
    SqlWrapper db;
    boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
    int curr_weekday = d.day_of_week().as_number();
    db << "SELECT * FROM lesson WHERE weekday='" << curr_weekday << "' and school_id=" << _school_id << ";";
    db.query("Get lessons for weekday by user");

    std::vector<Lesson> res_lesson;
    res_lesson.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_lesson.emplace_back(
                db.get_int(0, i),
                db.get_int(2, i),
                curr_weekday,
                db.get_str(5, i),
                db.get_str(6, i));
    }
    db.disconnect();
    return res_lesson;
}

std::vector<Lesson> User::get_lessons_by_weekday(int l_weekday) const {
    SqlWrapper db;
    db << "SELECT * FROM lesson WHERE weekday='" << l_weekday << "' and school_id=" << _school_id << ";";
    db.query("Get lessons for weekday by user");
    std::vector<Lesson> res_lesson;
    res_lesson.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_lesson.emplace_back(
                db.get_int(0, i),
                db.get_int(2, i),
                l_weekday,
                db.get_str(5, i),
                db.get_str(6, i));
    }
    db.disconnect();
    return res_lesson;
}

std::vector<Student> User::get_students() const {
    SqlWrapper db;
    db << "SELECT * FROM student WHERE school_id='" << _school_id << "';";
    db.query("Get students");

    std::vector<Student> res_students;
    res_students.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_students.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_str(2, i),
                db.get_int(3, i),
                db.get_str(5, i));
    }
    db.disconnect();
    return res_students;
}

User User::get_user(int user_id) {
    SqlWrapper db;
    db << "SELECT * FROM users WHERE id=" << user_id << ";";
    db.query("Get user by id");

    db.disconnect();
    return User(
            user_id,
            db.get_str(1),
            db.get_str(2),
            db.get_int(6),
            db.get_str(3),
            db.get_int(4),
            db.get_str(5));
}

int User::save(const std::string &username, const std::string &password, const std::string &email, int permission) {
    SqlWrapper db;
    db << "INSERT INTO users(email, login, password, permission) VALUES ('" << email << "', '" << username << "', '"
      << password << "', " << permission << ");";
    db.exec("Save user");
    db.disconnect();
    return 0;
}

int User::remove(int user_id) {
    SqlWrapper db;
    db << "DELETE FROM users WHERE id=" << user_id << ";";
    db.exec("Remove user");
    db.disconnect();
    return 0;
}

User User::get_user(const std::string &username) {
    SqlWrapper db;
    db << "SELECT * FROM users WHERE login=" << username << ";";
    db.query("Get user by username");

    db.disconnect();
    return User(
            db.get_int(0),
            db.get_str(1),
            username,
            db.get_int(6),
            db.get_str(3),
            db.get_int(4),
            db.get_str(5));
}

std::vector<cabinet> User::get_cabinets() const {
    SqlWrapper db;
    db << "select * from teacher join users on teacher.user_id=users.id where users.school_id=" << _school_id << ";";
    db.query("Get cabinets");

    std::vector<Cabinet> cabinets;
    cabinets.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        cabinets.emplace_back(
                db.get_int(0, i),
                db.get_int(2, i),
                db.get_str(1, i)
        );
    }
    db.disconnect();
    return cabinets;
}
