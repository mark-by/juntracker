//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/adminAPI.h"

AdminAPI::AdminAPI() {}

std::string AdminAPI::getStudent(std::string) {}

std::string AdminAPI::addStudent(std::string){}

std::string AdminAPI::deleteStudent(std::string) {}

std::string AdminAPI::addToScedule(std::string) {}

std::string AdminAPI::deleteFromScedule(std::string) {}

std::string AdminAPI::visitedCourse(std::string) {}

std::string AdminAPI::paidForCourse(std::string) {}

std::string AdminAPI::addNewCourse(std::string) {}

std::string AdminAPI::deleteCourse(std::string) {}

std::string AdminAPI::getStudentMarks(std::string) {}

std::string AdminAPI::getCourseMarks(std::string) {}

templates::Context AdminAPI::studentSerializer(Student) {}

templates::Context AdminAPI::scheduleSerializer(Schedule) {}

templates::Context AdminAPI::visitHistorySerializer(VisitHistory) {}

templates::Context AdminAPI::paymentHistorySerializer(PaymentHistory) {}

templates::Context AdminAPI::courseSerializer(Course) {}

templates::Context AdminAPI::journalSerializer(Journal) {}