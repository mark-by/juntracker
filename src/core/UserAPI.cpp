#include <UserAPI.h>
#include <user.h>


std::string UserAPI::signUp(const std::unordered_map<std::string, std::string> &data) {
    User::save(data.at("username"), data.at("password"), data.at("email"));

    return std::string();
}
