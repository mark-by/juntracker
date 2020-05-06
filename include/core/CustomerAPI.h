//
// Created by timofei on 22.04.2020.
//

#ifndef CORE_CUSTOMERAPI_H
#define CORE_CUSTOMERAPI_H

class CustomerAPI: public API {
public:
    CustomerAPI();
    std::string getMainPage(const std::string&);
};

#endif // CORE_CUSTOMERAPI_H
