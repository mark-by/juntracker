#include "lesson.h"

std::vector<Student> Lesson::get_students(int l_id) const {
    std::string query = "SELECT student_id FROM visit WHERE lesson_id='" + std::to_string(l_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<int> student_ids;
    for (int i = 0; i < PQntuples(result); i++) {
        student_ids.push_back(atoi(PQgetvalue(result, i, 0)));
    }

    std::vector<Student> res_students;
    for (auto s_id : student_ids) {
        query = "SELECT * FROM student WHERE id='" + std::to_string(s_id) + "';";
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        std::string s_name = std::string(PQgetvalue(result, 0, 1));
        std::string s_surname = std::string(PQgetvalue(result, 0, 2));
        int s_age = atoi(PQgetvalue(result, 0, 3));
        Student curr_student(s_id, s_name, s_surname, s_age);
        res_students.push_back(curr_student);
    }

    return res_students;
}

Teacher Lesson::get_teacher(int l_id) const {
    std::string query = "SELECT teacher_id FROM visit WHERE lesson_id='" + std::to_string(l_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int t_id = atoi(PQgetvalue(result, 0, 0));

    query = "SELECT * FROM teacher WHERE id='" + std::to_string(t_id) + "';";
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string t_name = std::string(PQgetvalue(result, 0, 1));
    std::string t_surname = std::string(PQgetvalue(result, 0, 2));
    int t_salary = atoi(PQgetvalue(result, 0, 3));
    std::string t_description = std::string(PQgetvalue(result, 0, 4));
    Teacher res_teacher(t_id, t_name, t_surname, t_salary, t_description);

    return res_teacher;
}

std::string Lesson::get_weekday(std::string d_date) const {
    std::string query = "SELECT weekday FROM day WHERE date='" + d_date + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::string res_weekday = PQgetvalue(result, 0, 0);
    return res_weekday;
}

Lesson Lesson::get_lesson(int l_id) const {
    std::string query = "SELECT * FROM lesson WHERE id=" + std::to_string(l_id) + ";";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    int l_course_id = atoi(PQgetvalue(result, 0, 1));
    int l_cabinet = atoi(PQgetvalue(result, 0, 2));
    int l_teacher_id = atoi(PQgetvalue(result, 0, 3));
    std::string l_weekday = std::string(PQgetvalue(result, 0, 4));
    std::string l_start_time = std::string(PQgetvalue(result, 0, 5));
    std::string l_end_time = std::string(PQgetvalue(result, 0, 6));
    int l_day_id = atoi(PQgetvalue(result, 0, 7));
    auto res_lesson = Lesson(l_id, l_course_id, l_cabinet, l_teacher_id, l_weekday, l_start_time, l_end_time, l_day_id);
    return res_lesson;
}

int Lesson::add_lesson(const Lesson& lesson) const {
    std::ostringstream s;
    s << "INSERT INTO lesson VALUES (" << std::to_string(lesson.id) << ", "
      << std::to_string(lesson.course_id) << ", " << std::to_string(lesson.cabinet) << ", "
      << std::to_string(lesson.teacher_id) << ", '" << lesson.weekday << "', '"
      << lesson.start_time << "', '" << lesson.end_time << "', "
      << std::to_string(lesson.day_id) << ");";

    std::string query = s.str();
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}

int Lesson::delete_lesson(int l_id) const {
    std::string query = "DELETE * FROM lesson WHERE id=" + std::to_string(l_id) + ";";
    if (!postgres.exec(query)) {
        return -1;
    }
    return 0;
}



