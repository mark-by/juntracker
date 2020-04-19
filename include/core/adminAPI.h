//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

class AdminAPI {
public:
    AdminAPI();
    std::string getStudent(Request);
    std::string addStudent(Request);
    std::string deleteStudent(Request);

    std::string addToScedule(Request);
    std::string deleteFromScedule(Request);

    std::string visitedCourse(Request);

    std::string paidForCourse(Request);
    std::string addNewCourse(Request);
    std::string deleteCourse(Request);

    std::string getStudentMarks(Request);
    std::string getCourseMarks(Request);

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
