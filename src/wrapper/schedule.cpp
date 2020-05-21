#include "schedule.h"

std::vector<Day> Schedule::get_schedule_by_student(int s_id) const {
    std::string query = "SELECT course_id FROM payment WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    std::vector<int> s_courses;
    for (int i = 0; i < PQntuples(result); i++) {
        s_courses.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<int> lesson_ids;
    for (auto c_id : s_courses) {
        query = "SELECT day_id FROM lesson WHERE course_id='" + std::to_string(c_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        for (int j = 0; j < PQntuples(result); j++) {
            lesson_ids.push_back(atoi(PQgetvalue(result, j, 0)));
        }
    }

    std::vector<Day> res_days;
    for (auto l_id : lesson_ids) {
        query = "SELECT * FROM day WHERE id='" + std::to_string(l_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        int d_id = atoi(PQgetvalue(result, 0, 0));
        std::string d_weekday = std::string(PQgetvalue(result, 0, 1));
        std::string d_date = std::string(PQgetvalue(result, 0, 2));
        Day curr_day(d_id, d_weekday, d_date);
        res_days.push_back(curr_day);
    }
    return res_days;
}

std::vector<Day> Schedule::get_schedule_by_course(int c_id) const {
    std::string query = "SELECT day_id FROM lesson WHERE course_id='" + std::to_string(c_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    std::vector<int> lesson_ids;
    for (int i = 0; i < PQntuples(result); i++) {
        lesson_ids.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<Day> res_days;
    for (auto l_id : lesson_ids) {
        query = "SELECT * FROM day WHERE id='" + std::to_string(l_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        int d_id = atoi(PQgetvalue(result, 0, 0));
        std::string d_weekday = std::string(PQgetvalue(result, 0, 1));
        std::string d_date = std::string(PQgetvalue(result, 0, 2));
        Day curr_day(d_id, d_weekday, d_date);
        res_days.push_back(curr_day);
    }
    return res_days;
}

std::vector<Day> Schedule::get_schedule_by_teacher(int t_id) const {
    std::string query = "SELECT id FROM course WHERE teacher_id='" + std::to_string(t_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    std::vector<int> t_courses;
    for (int i = 0; i < PQntuples(result); i++) {
        t_courses.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<int> lesson_ids;
    for (auto c_id : t_courses) {
        query = "SELECT day_id FROM lesson WHERE course_id='" + std::to_string(c_id) + "';";

        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        for (int j = 0; j < PQntuples(result); j++) {
            lesson_ids.push_back(atoi(PQgetvalue(result, j, 0)));
        }
    }

    std::vector<Day> res_days;
    for (auto l_id : lesson_ids) {
        query = "SELECT * FROM day WHERE id='" + std::to_string(l_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        int d_id = atoi(PQgetvalue(result, 0, 0));
        std::string d_weekday = std::string(PQgetvalue(result, 0, 1));
        std::string d_date = std::string(PQgetvalue(result, 0, 2));
        Day curr_day(d_id, d_weekday, d_date);
        res_days.push_back(curr_day);
    }
    return res_days;
}
