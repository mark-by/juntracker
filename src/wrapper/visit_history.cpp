#include "visit_history.h"

std::vector<Visit> VisitHistory::get_visits_by_student(int s_id) const {
    std::string query = "SELECT * FROM visit WHERE student_id='" + std::to_string(s_id) + "';";
    PGresult *result = nullptr;
    if (!postgres.query(query, &result)) {
        throw std::exception();
    }
    std::vector<Visit> res_visits;
    for (int i = 0; i < PQntuples(result); i++) {
        int p_id = atoi(PQgetvalue(result, i, 0));
        int c_id = atoi(PQgetvalue(result, i, 2));
        std::string p_date = PQgetvalue(result, i, 3);
        Visit new_visit(p_id, s_id, c_id, p_date);
        res_visits.push_back(new_visit);
    }

    return res_visits;
}

std::vector<Visit> VisitHistory::get_visits_by_course(int c_id) const {
    std::string query = "SELECT * FROM visit WHERE course_id='" + std::to_string(c_id) + "';";
        PGresult *result = nullptr;
        if (!postgres.query(query, &result)) {
            throw std::exception();
        }
        std::vector<Visit> res_visits;
        for (int i = 0; i < PQntuples(result); i++) {
            int p_id = atoi(PQgetvalue(result, i, 0));
            int s_id = atoi(PQgetvalue(result, i, 1));
            std::string p_date = PQgetvalue(result, i, 3);
            Visit new_visit(p_id, s_id, c_id, p_date);
            res_visits.push_back(new_visit);
        }

        return res_visits;
}

