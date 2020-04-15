#ifndef _VISIT_HISTORY_H_
#define _VISIT_HISTORY_H_

#include <string>
#include <vector>

#include "visit.h"

class VisitHistory {
 public:
    explicit VisitHistory();

    std::vector<Visit> get_visits_by_student(int id) const;
    std::vector<Visit> get_visits_by_course(int id) const;
    std::vector<Visit> get_visits_by_date(std::string start, std::string end) const;

 private: 
    std::vector<Visit> visits;
};

#endif  // _VISIT_HISTORY_H_