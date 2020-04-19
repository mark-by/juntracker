//
// Created by timofei on 14.04.2020.
//

#include "../../include/core/adminAPI.h"

AdminAPI::AdminAPI() {}

std::string AdminAPI::getStudent(Request) {}

std::string AdminAPI::addStudent(Request){}

std::string AdminAPI::deleteStudent(Request) {}

std::string AdminAPI::addToScedule(Request) {}

std::string AdminAPI::deleteFromScedule(Request) {}

std::string AdminAPI::visitedCourse(Request) {}

std::string AdminAPI::paidForCourse(Request) {}

std::string AdminAPI::addNewCourse(Request) {}

std::string AdminAPI::deleteCourse(Request) {}

std::string AdminAPI::getStudentMarks(Request) {}

std::string AdminAPI::getCourseMarks(Request) {}

templates::Context AdminAPI::studentSerializer(Student) {}

templates::Context AdminAPI::scheduleSerializer(Schedule) {}

templates::Context AdminAPI::visitHistorySerializer(VisitHistory) {}

templates::Context AdminAPI::paymentHistorySerializer(PaymentHistory) {}

templates::Context AdminAPI::courseSerializer(Course) {}

templates::Context AdminAPI::journalSerializer(Journal) {}