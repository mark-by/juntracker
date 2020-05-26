#ifndef JUNTRACKER_USERAPI_H
#define JUNTRACKER_USERAPI_H
#include <string>
#include <unordered_map>

class UserAPI {
public:
    UserAPI() = default;

    std::string loginPage();
    std::string registerPage();
    std::string signUp(const std::unordered_map<std::string, std::string> &data);
    std::string signIn(const std::string& username, const std::string& password);
};
#endif //JUNTRACKER_USERAPI_H
