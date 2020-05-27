#include <UserAPI.h>
#include <user.h>
#include <context/context.h>
#include <session.h>


std::string UserAPI::signUp(const std::unordered_map<std::string, std::string> &data) {
    std::string username;
    std::string password;
    std::string email;
    try {
        username = data.at("username");
        password = data.at("password");
        email = data.at("email");
    } catch (...) {
        return "";
    }
    if (!User::save(username, password, email)) {
        return "";
    }
    auto user = User::get_user(username);
    auto session = Session::create_session(username, password);
    return session.cookie();
}

std::string UserAPI::registerPage() {
    templates::Context context;
    _render.set("register.html");
    return _render.render(context);
}

std::string UserAPI::loginPage() {
    templates::Context context;
    _render.set("login.html");
    return _render.render(context);
}

std::string UserAPI::signIn(const std::string &username, const std::string &password) {
    auto session = Session::create_session(username, password);
    return session.cookie();
}
