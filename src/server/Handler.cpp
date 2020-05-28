//
// Created by gg on 15.04.2020.
//

#include "Handler.h"
#include "../database/session.h"


Response Handler::customerHandler(Request request, const User &user) {
    Response response("<html><h1>Hello world!(From Customer)</h1></html>");
    // Response response(customer.get(std::stoi(request._data("id"))));
    return response;
}

Response Handler::teacherHandler(Request request, const User &user) {
    Response response("<html><h1>Hello world! (From Teacher)</h1></html>");
    // Response response(tutor.get(boost::lexical_cast<int>(request._data("id"))));
    return response;
}

Response Handler::adminHandler(Request request, const User &user) {
    if (request.method() == "GET") {
        if (request.path() == "/") {
            std::cout << "/\n";
            Response response(adminApi.getMainPage(user.id()));
            return response;
        }

        if (request.path() == "/students") {
            std::cout << "/student\n";
            Response response(adminApi.getPageStudents(user.id()));
            return response;
        }

        if (request.path() == "/student") {
            std::cout << "/student\n";
            Response response(adminApi.findStudent(request.data("name")));
            return response;
        }

    } else {
        if (request.path() == "/save_current_lesson") {
            std::cout << "/save_current_lesson\n";
            Response response(adminApi.saveCurrentLesson(request.dataTable()));
            return response;
        }

        if (request.path() == "/delete_student") {
            std::cout << "/delete_student\n";
            Response response(adminApi.deleteStudent(std::stoi(request.data("id"))));
            return response;
        }

        if (request.path() == "/create_student") {
            std::cout << "/create_student\n";
            Response response(adminApi.createStudent(request.dataTable()));
            return response;
        }

        if (request.path() == "/add_course") {
            std::cout << "/add_course\n";
            Response response(adminApi.addCourse(request.dataTable()));
            return response;
        }

        if (request.path() == "/delete_course") {
            std::cout << "/delete_course\n";
            Response response(adminApi.deleteCourse(std::stoi(request.data("id"))));
            return response;
        }
    }
    return Response(status::BadRequest);
}

std::shared_ptr<User> Handler::authorizationHandler(Request request) {
    if (request.cookie("session_id").empty()) {
        std::cout << "EMPTY SESSIONID" << std::endl;
        return nullptr;
    }
    try {
        return std::make_shared<User>(Session::get_user(request.cookie("session_id")));
    } catch (...) {
        std::cout << "FAIL TO GET USER" << std::endl;
        return nullptr;
    }
}

Response Handler::loginHandler(Request request) {
    std::string session_id;

    if (request.path() == "/login") {
        if (request.method() == "GET") {
            return Response(userApi.loginPage());
        } else {
            session_id = userApi.signIn(request.data("username"), request.data("password"));
        }
    } else {
        if (request.method() == "GET") {
            std::cout << "registerPage" << std::endl;
            return Response(userApi.registerPage());
        } else {
            std::cout << "signUP" << std::endl;
            session_id = userApi.signUp(request.dataTable());
            std::cout << "HERE SHOULD BE SESSION ID" << std::endl;
            std::cout << session_id << std::endl;
        }
    }

    if (session_id.empty()) {
        return Response(status::Forbidden);
    } else {
        std::cout << session_id << std::endl;
        Response tmp;
        tmp.setCookie("session_id", session_id, 10);  // 10 days living cookie
        tmp.setHeader("Location", "/");
        tmp.setStatus(status::MovedPermanently);
        return tmp;
    }
}
