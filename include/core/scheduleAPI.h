//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_SCHEDULEAPI_H
#define CORE_SCHEDULEAPI_H

class ScheduleAPI {
public:
    ScheduleAPI();
    std::string getStudentSchedule(std::string);
    std::string getTeacherSchedule(std::string);
    std::string getGeneralSchedule(std::string);
    templates::Context scheduleSerializer(Schedule);
private:
    managerSchedule schedule;
};

#endif //CORE_SCHEDULEAPI_H
