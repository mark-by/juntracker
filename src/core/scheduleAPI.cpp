//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/scheduleAPI.h"

ScheduleAPI::ScheduleAPI() {}

std::string ScheduleAPI::getStudentSchedule(Request) {}

std::string ScheduleAPI::getTeacherSchedule(Request) {}

std::string ScheduleAPI::getGeneralSchedule(Request) {}

templates::Context ScheduleAPI::scheduleSerializer(Schedule) {}
