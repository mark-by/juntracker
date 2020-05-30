#include "user.h"
//#include <common_sql.hpp>

std::vector<Teacher> User::get_teachers() const {
    SqlWrapper db;
    db << "select teacher.id, name, surname, age, salary, tel_number, description, avatar"
       << " from teacher join users on teacher.user_id=users.id where users.school_id=" << _school_id << ";";
    db.exec("Get teachers");

    std::vector<Teacher> teachers;
    teachers.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        teachers.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_str(2, i),
                db.get_int(3, i),
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
    db.exec("Get lessons for weekday by user");

    std::vector<Lesson> res_lesson;
    res_lesson.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_lesson.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_int(7, i)
                );
    }
    db.disconnect();
    return res_lesson;
}

std::vector<Lesson> User::get_lessons_by_weekday(int l_weekday) const {
    SqlWrapper db;
    db << "SELECT * FROM lesson WHERE weekday='" << l_weekday << "' and school_id=" << _school_id << ";";
    db.exec("Get lessons for weekday by user");
    std::vector<Lesson> res_lesson;
    res_lesson.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_lesson.emplace_back(
                db.get_int(0, i),
                db.get_int(1, i),
                db.get_int(2, i),
                db.get_int(3, i),
                db.get_int(4, i),
                db.get_str(5, i),
                db.get_str(6, i),
                db.get_int(7, i)
        );
    }
    db.disconnect();
    return res_lesson;
}

std::vector<Student> User::get_students() const {
    SqlWrapper db;
    db << "SELECT * FROM student WHERE school_id='" << _school_id << "';";
    db.exec("Get students");

    std::vector<Student> res_students;
    res_students.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        res_students.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_str(2, i),
                db.get_int(3, i),
                db.get_str(4, i),
                db.get_str(5, i),
                db.get_str(6, i)
                );
    }
    db.disconnect();
    return res_students;
}

User User::get_user(int user_id) {
    SqlWrapper db;
    db << "SELECT * FROM users WHERE id=" << user_id << ";";
    db.exec("Get user by id");

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

int User::save(const std::string &username, const std::string &password,
        const std::string &email, int permission, int school_id) {
    SqlWrapper db;
    if (school_id < 0) {
        db << "insert into schools(school_title) values ('" << username << "');";
        db.exec("Create school");
        db << "select id from schools where school_title='" << username << "';";
        db.exec("Get new school id");
        school_id = db.get_int(0);
    }
    db << "INSERT INTO users(email, login, password, permission, school_id) VALUES ('" << email << "', '" << username << "', '"
      << password << "', " << permission << ", " << school_id << ");";
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
    db.exec("Get user by username");

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

std::vector<Cabinet> User::get_cabinets() const {
    SqlWrapper db;
    db << "select * from teacher join users on teacher.user_id=users.id where users.school_id=" << _school_id << ";";
    db.exec("Get cabinets");

    std::vector<Cabinet> cabinets;
    cabinets.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        cabinets.emplace_back(
                db.get_int(0, i),
                db.get_str(1, i),
                db.get_int(2, i)
        );
    }

    db.disconnect();

    return cabinets;
}

std::vector<Course> User::get_courses() const {
    SqlWrapper db;

    db << "SELECT * FROM course WHERE school_id='" << _school_id << "';";
    db.exec("Get courses");

    std::vector<Course> courses;
    courses.reserve(db.count_tupls());
    for (int i = 0; i < db.count_tupls(); i++) {
        courses.emplace_back(
                db.get_int(0, 0),
                db.get_str(1, 0),
                db.get_int(2, 0),
                db.get_int(3, 0),
                db.get_int(4, 0)
        );
    }

    db.disconnect();
    return courses;
}
