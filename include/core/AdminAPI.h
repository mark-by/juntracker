//
// Created by timofei on 14.04.2020.
//

#ifndef CORE_ADMINAPI_H
#define CORE_ADMINAPI_H

class AdminAPI: public API {
public:
    AdminAPI();

    std::string getMainPage(const std::string&);
    int saveCurrentLesson(std::map<std::string, std::string>);
    std::string findStudent(const std::string&);
    int deleteStudent(std::vector<string>);
    int createStudent(const std::string&);
    std::string getStudentsBy(std::map<std::string, std::string>);
    std::string getPageStudents(int);

    int addCourse(const std::string&);
    int deleteCourse(const std::string&);

    std::string getPaymentsByStudent(const std::string&);

    //NEED TO ADD MORE
};

#endif //CORE_ADMINAPI_H
