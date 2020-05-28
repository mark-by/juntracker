#include <UserAPI.h>
#include <user.h>
#include <context/context.h>
#include <session.h>
#include <iostream>


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
    try {
        User::save(username, password, email);
    } catch (...) {
        return "";
    }
    try {
        return Session::create_session(username, password).cookie();
    } catch(...) {
        return "";
    }
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
    try {
        return Session::create_session(username, password).cookie();
    } catch(...) {
        return "";
    }
}
