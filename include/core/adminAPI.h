//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

class AdminAPI {
public:
    AdminAPI();
    std::string getStudent(std::string);
    std::string addStudent(std::string);
    std::string deleteStudent(std::string);
    std::string addToScedule(std::string);
    std::string deleteFromScedule(std::string);
    std::string visitedCourse(std::string);
    std::string paidForCourse(std::string);
    std::string addNewCourse(std::string);
    std::string deleteCourse(std::string);
    std::string getStudentMarks(std::string);
    std::string getCourseMarks(std::string);
    templates::Context studentSerializer(Student);
    templates::Context scheduleSerializer(Schedule);
    templates::Context visitHistorySerializer(VisitHistory);
    templates::Context paymentHistorySerializer(PaymentHistory);
    templates::Context courseSerializer(Course);
    templates::Context journalSerializer(Journal);
private:
    managerStudent student;
    managerVisitHistory visits;
    managerPaymentHistory payments;
    managerSchedule schedule;
    managerJournal journal;
};

#endif //CORE_ADMINAPI_H
