#include "visit_history.h"

std::vector<Visit> VisitHistory::get_visits_by_student(int s_id) const {
    auto postgres = connect();
    const std::string format = "%a, %d %b %Y %H:%M:%S";
    DateTimeConverter converter(format);
    std::string query = "SELECT * FROM visit WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Visit> res_visits;
    for (int i = 0; i < PQntuples(result); i++) {
        int v_id = atoi(PQgetvalue(result, i, 0));
        int v_was_in_class = atoi(PQgetvalue(result, i, 1));
        std::string str_v_date = std::string(PQgetvalue(result, 0, 2));
        boost::posix_time::ptime v_date = converter.convert(str_v_date);
        Visit new_visit(v_id, v_was_in_class, v_date);
        res_visits.push_back(new_visit);
    }

    return res_visits;
}

std::vector<Visit> VisitHistory::get_visits_by_lesson(int c_id) const {
    auto postgres = connect();
    const std::string format = "%a, %d %b %Y %H:%M:%S";
    DateTimeConverter converter(format);
    std::string query = "SELECT * FROM visit WHERE lesson_id='" + std::to_string(c_id) + "' and was_in_class=true;";
        PGresult *result = nullptr;
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        std::vector<Visit> res_visits;
        for (int i = 0; i < PQntuples(result); i++) {
            int v_id = atoi(PQgetvalue(result, i, 0));
            int v_was_in_class = atoi(PQgetvalue(result, i, 1));
            std::string str_v_date = std::string(PQgetvalue(result, 0, 2));
            boost::posix_time::ptime v_date = converter.convert(str_v_date);
            Visit new_visit(v_id, v_was_in_class, v_date);
            res_visits.push_back(new_visit);
        }
        return res_visits;
}

