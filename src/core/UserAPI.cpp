#include <UserAPI.h>
#include <user.h>


std::string UserAPI::signUp(const std::unordered_map<std::string, std::string> &data) {
    User::save(data.at("username"), data.at("password"), data.at("email"));

    return std::string();
}

std::string UserAPI::registerPage() {
    return "Register";
}

std::string UserAPI::loginPage() {
    return "Login";
}

std::string UserAPI::signIn(const std::string &username, const std::string &password) {
    return std::string();
}
