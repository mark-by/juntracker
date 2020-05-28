#include "user.h"
#include <utils.hpp>

std::vector<Lesson> User::get_current_lessons() const {
    SqlWrapper postgres;
    boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
    int curr_weekday = d.day_of_week().as_number();
    std::string query = "SELECT * FROM lesson WHERE weekday='" + std::to_string(curr_weekday) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::vector<Lesson> res_lesson;
    for (int i = 0; i < PQntuples(result); i++) {
        int l_id = atoi(PQgetvalue(result, i, 0));
        int l_cabinet = atoi(PQgetvalue(result, i, 2));
        std::string l_start_time = std::string(PQgetvalue(result, i, 5));
        std::string l_end_time = std::string(PQgetvalue(result, i, 6));
        auto curr_lesson = Lesson(l_id, l_cabinet, curr_weekday, l_start_time, l_end_time);
        res_lesson.push_back(curr_lesson);
    }
    postgres.disconnect();
    return res_lesson;
}

std::vector<Lesson> User::get_lessons_by_weekday(int l_weekday) const {
    SqlWrapper postgres;
    std::string query = "SELECT * FROM lesson WHERE weekday='" + std::to_string(l_weekday) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::vector<Lesson> res_lesson;
    for (int i = 0; i < PQntuples(result); i++) {
        int l_id = atoi(PQgetvalue(result, i, 0));
        int l_cabinet = atoi(PQgetvalue(result, i, 2));
        std::string l_start_time = std::string(PQgetvalue(result, i, 5));
        std::string l_end_time = std::string(PQgetvalue(result, i, 6));
        auto curr_lesson = Lesson(l_id, l_cabinet, l_weekday, l_start_time, l_end_time);
        res_lesson.push_back(curr_lesson);
    }
    postgres.disconnect();
    return res_lesson;
}

std::vector<Student> User::get_students() const {
    SqlWrapper postgres;
    std::string query = "SELECT * FROM student WHERE user_id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::vector<Student> res_students;
    for (int i = 0; i < PQntuples(result); i++) {
        int student_id = atoi(PQgetvalue(result, i, 0));
        std::string s_name = std::string(PQgetvalue(result, i, 1));
        std::string s_surname = std::string(PQgetvalue(result, i, 2));
        int s_age = atoi(PQgetvalue(result, i, 3));
        res_students.emplace_back(student_id, s_name, s_surname, s_age);
    }
    postgres.disconnect();
    return res_students;
}

User User::get_user(int user_id) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM users WHERE id=" + std::to_string(user_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        postgres.disconnect();
        throw std::exception();
    }
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    std::string u_login = std::string(PQgetvalue(result, 0, 2));
    std::string u_password = std::string(PQgetvalue(result, 0, 3));
    int u_permission = atoi(PQgetvalue(result, 0, 4));
    postgres.disconnect();
    return User(user_id, u_email, u_login, u_password, u_permission);
}

int User::save(const std::string &username, const std::string &password, const std::string &email) {
    SqlWrapper postgres;

    if(!postgres.is_connected()) {
        postgres.disconnect();
        return 1;
    }

    std::ostringstream s;
    std::string table_name = "users";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO users VALUES (" << std::to_string(count_rows + 1) << ", '" << email
      << "', '" << username << "', '" << password << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

int User::remove(int user_id) {
    SqlWrapper postgres;

    std::string query = "DELETE FROM users WHERE id=" + std::to_string(user_id) + ";";
    if (!postgres.exec(query)) {
        postgres.disconnect();
        return -1;
    }
    postgres.disconnect();
    return 0;
}

User User::get_user(const std::string &username) {
    SqlWrapper postgres;

    std::string query = "SELECT * FROM users WHERE login=" + username + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    int user_id = std::stoi(PQgetvalue(result, 0, 0));
    std::string u_password = std::string(PQgetvalue(result, 0, 3));
    int u_permission = atoi(PQgetvalue(result, 0, 4));
    std::string login = username;
    postgres.disconnect();
    return User(user_id, u_email, login, u_password, u_permission);
}
