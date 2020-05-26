#include "user.h"

std::vector<Lesson> User::get_current_lessons() const {
    boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
    int curr_weekday = d.day_of_week().as_number();
    std::string query = "SELECT * FROM lesson WHERE weekday='" + std::to_string(curr_weekday) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Lesson> res_lesson;
    for (int i = 0; i < PQntuples(result); i++) {
        int l_id = atoi(PQgetvalue(result, i, 0));
        int l_cabinet = atoi(PQgetvalue(result, i, 2));
        std::string l_start_time = std::string(PQgetvalue(result, i, 5));
        std::string l_end_time = std::string(PQgetvalue(result, i, 6));
        auto curr_lesson = Lesson(l_id, l_cabinet, curr_weekday, l_start_time, l_end_time, postgres);
        res_lesson.push_back(curr_lesson);
    }
    return res_lesson;
}

std::vector<Lesson> User::get_lessons_by_weekday(int l_weekday) const {
    std::string query = "SELECT * FROM lesson WHERE weekday='" + std::to_string(l_weekday) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Lesson> res_lesson;
    for (int i = 0; i < PQntuples(result); i++) {
        int l_id = atoi(PQgetvalue(result, i, 0));
        int l_cabinet = atoi(PQgetvalue(result, i, 2));
        std::string l_start_time = std::string(PQgetvalue(result, i, 5));
        std::string l_end_time = std::string(PQgetvalue(result, i, 6));
        auto curr_lesson = Lesson(l_id, l_cabinet, l_weekday, l_start_time, l_end_time, postgres);
        res_lesson.push_back(curr_lesson);
    }
    return res_lesson;
}

Student User::get_student() const {
    std::string query = "SELECT * FROM student WHERE user_id='" + std::to_string(this->_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int student_id = atoi(PQgetvalue(result, 0, 0));

    std::string s_name = std::string(PQgetvalue(result, 0, 1));
    std::string s_surname = std::string(PQgetvalue(result, 0, 2));
    int s_age = atoi(PQgetvalue(result, 0, 3));
    Student res_student(student_id, s_name, s_surname, s_age, postgres);

    return res_student;
}

User User::get_user(int user_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "SELECT * FROM users WHERE id=" + std::to_string(user_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string u_email = std::string(PQgetvalue(result, 0, 1));
    std::string u_login = std::string(PQgetvalue(result, 0, 2));
    std::string u_password = std::string(PQgetvalue(result, 0, 3));
    auto res_user = User(user_id, u_email, u_login, u_password);
    return res_user;
}

int User::save(const std::string& username, const std::string& password, const std::string& email) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::ostringstream s;
    std::string table_name = "users";
    int count_rows = postgres.count_rows(table_name);
    s << "INSERT INTO users VALUES (" << std::to_string(count_rows + 1) << ", '" << email
    << "', '" << username << "', '" << password << "');";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int User::remove(int user_id) {
    std::string filepath = "config.txt";
    std::ifstream fin(filepath);
    std::string conninfo;
    while (getline(fin, conninfo)) {}
    fin.close();
    PGconn *conn = PQconnectdb(conninfo.c_str());
    SqlWrapper postgres(conn);

    std::string query = "DELETE FROM users WHERE id=" + std::to_string(user_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

