#ifndef JUNTRACKER_USERAPI_H
#define JUNTRACKER_USERAPI_H
#include <string>
#include <unordered_map>
#include <template/template.h>

class UserAPI {
public:
    UserAPI() = default;

    std::string loginPage();
    std::string registerPage();
    std::string signUp(const std::unordered_map<std::string, std::string> &data);
    std::string signIn(const std::string& username, const std::string& password);
private:
    templates::Template _render;
};
#endif //JUNTRACKER_USERAPI_H
