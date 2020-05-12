//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_TEACHERAPI_H
#define CORE_TEACHERAPI_H


class TeacherAPI: public API {
public:
    TeacherAPI();
    std::string getMainPage(const std::string&);
    int rate(std::unordered_map<std::string, std::string> &);//
};


#endif //CORE_TEACHERAPI_H
