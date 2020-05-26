#include "schedule.h"

std::vector<Lesson> Schedule::get_schedule_by_student(int s_id) const {
    std::string query = "SELECT course_id FROM payment WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    std::vector<int> s_courses;
    for (int i = 0; i < PQntuples(result); i++) {
        s_courses.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<Lesson> res_lessons;
    std::vector<int> lesson_ids;
    for (auto c_id : s_courses) {
        query = "SELECT * FROM lesson WHERE course_id='" + std::to_string(c_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        for (int j = 0; j < PQntuples(result); j++) {
            int l_id = atoi(PQgetvalue(result, 0, 0));
            int l_cabinet = atoi(PQgetvalue(result, 0, 2));
            int l_weekday = atoi(PQgetvalue(result, 0, 4));
            std::string l_start_time = std::string(PQgetvalue(result, 0, 5));
            std::string l_end_time = std::string(PQgetvalue(result, 0, 6));
            auto cur_lesson = Lesson(l_id, l_cabinet, l_weekday, l_start_time, l_end_time, postgres);
            res_lessons.push_back(cur_lesson);
        }
    }
    return res_lessons;
}

std::vector<Lesson> Schedule::get_schedule_by_course(int c_id) const {
    std::string query = "SELECT * FROM lesson WHERE course_id='" + std::to_string(c_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Lesson> res_lessons;
    for (int j = 0; j < PQntuples(result); j++) {
        int l_id = atoi(PQgetvalue(result, 0, 0));
        int l_cabinet = atoi(PQgetvalue(result, 0, 2));
        int l_weekday = atoi(PQgetvalue(result, 0, 4));
        std::string l_start_time = std::string(PQgetvalue(result, 0, 5));
        std::string l_end_time = std::string(PQgetvalue(result, 0, 6));
        auto cur_lesson = Lesson(l_id, l_cabinet, l_weekday, l_start_time, l_end_time, postgres);
        res_lessons.push_back(cur_lesson);
    }
    return res_lessons;
}

std::vector<Lesson> Schedule::get_schedule_by_teacher(int t_id) const {
    std::string query = "SELECT id FROM course WHERE teacher_id='" + std::to_string(t_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }

    std::vector<int> t_courses;
    for (int i = 0; i < PQntuples(result); i++) {
        t_courses.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<Lesson> res_lessons;
    std::vector<int> lesson_ids;
    for (auto t_id : t_courses) {
        query = "SELECT * FROM lesson WHERE course_id='" + std::to_string(t_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        for (int j = 0; j < PQntuples(result); j++) {
            int l_id = atoi(PQgetvalue(result, 0, 0));
            int l_cabinet = atoi(PQgetvalue(result, 0, 2));
            int l_weekday = atoi(PQgetvalue(result, 0, 4));
            std::string l_start_time = std::string(PQgetvalue(result, 0, 5));
            std::string l_end_time = std::string(PQgetvalue(result, 0, 6));
            auto cur_lesson = Lesson(l_id, l_cabinet, l_weekday, l_start_time, l_end_time, postgres);
            res_lessons.push_back(cur_lesson);
        }
    }
    return res_lessons;
}
