#include <UserAPI.h>
#include <user.h>
#include <context/context.h>


std::string UserAPI::signUp(const std::unordered_map<std::string, std::string> &data) {
    User::save(data.at("username"), data.at("password"), data.at("email"));

    return std::string();
}

std::string UserAPI::registerPage() {
    return "Register";
}

std::string UserAPI::loginPage() {
    templates::Context context;
    _render.set("login.html");
    return _render.render(context);
}

std::string UserAPI::signIn(const std::string &username, const std::string &password) {
    templates::Context context;
    _render.set("register.html");
    return _render.render(context);
}
