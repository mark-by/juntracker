#ifndef _VISIT_HISTORY_H_
#define _VISIT_HISTORY_H_

#include <string>
#include <vector>

#include "visit.h"
#include "http/datetime.h"

class VisitHistory {
 public:
    explicit VisitHistory(std::vector<Visit> visits): visits(visits) {}

    std::vector<Visit> get_visits_by_student(int id) const;
    std::vector<Visit> get_visits_by_lesson(int id) const;

 private: 
    std::vector<Visit> visits;
};

#endif  // _VISIT_HISTORY_H_