//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/scheduleAPI.h"

ScheduleAPI::ScheduleAPI() {}

std::string ScheduleAPI::getStudentSchedule(std::string) {}

std::string ScheduleAPI::getTeacherSchedule(std::string) {}

std::string ScheduleAPI::getGeneralSchedule(std::string) {}

templates::Context ScheduleAPI::scheduleSerializer(Schedule) {}
