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
        std::cout << username << " " << password << " " << email << std::endl;
        User::save(username, password, email);
        std::cout << "saved" << std::endl;
    } catch (...) {
        std::cout << "user save fail" << std::endl;
        return "";
    }
    try {
        std::cout << "username: " << username << " password: " << password << std::endl;
        return Session::create_session(username, password).cookie();
    } catch(...) {
        std::cout << "create session fail" << std::endl;
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
    std::cout << username << " " << password << std::endl;
    try {
        return Session::create_session(username, password).cookie();
    } catch(...) {
        std::cout << "create_session fail" << std::endl;
        return "";
    }
}
