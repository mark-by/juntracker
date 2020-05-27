#ifndef _VISIT_HISTORY_H_
#define _VISIT_HISTORY_H_

#include <string>
#include <vector>

#include "visit.h"
#include "http/datetime.h"

class VisitHistory {
 public:
    VisitHistory(SqlWrapper& postgres)
    : postgres(postgres) {}
    explicit VisitHistory(std::vector<Visit> visits)
    : visits(visits) {}

//    std::vector<Visit> get_visits_by_student(int id) const;
//    std::vector<Visit> get_visits_by_lesson(int id) const;
    std::vector<Visit> get_visits_by_date(std::string start, std::string end) const;

 private: 
    std::vector<Visit> visits;

    SqlWrapper postgres;
};

#endif  // _VISIT_HISTORY_H_