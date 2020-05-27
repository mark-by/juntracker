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
            Response response(admin.getMainPage(user.id()));
            return response;
        }

        if (request.path() == "/students") {
            std::cout << "/student\n";
            Response response(admin.getPageStudents(user.id()));
            return response;
        }

        if (request.path() == "/student") {
            std::cout << "/student\n";
            Response response(admin.findStudent(request.data("name")));
            return response;
        }

    } else {
        if (request.path() == "/save_current_lesson") {
            std::cout << "/save_current_lesson\n";
            Response response(admin.saveCurrentLesson(request.dataTable()));
            return response;
        }

        if (request.path() == "/delete_student") {
            std::cout << "/delete_student\n";
            Response response(admin.deleteStudent(std::stoi(request.data("id"))));
            return response;
        }

        if (request.path() == "/create_student") {
            std::cout << "/create_student\n";
            Response response(admin.createStudent(request.dataTable()));
            return response;
        }

        if (request.path() == "/add_course") {
            std::cout << "/add_course\n";
            Response response(admin.addCourse(request.dataTable()));
            return response;
        }

        if (request.path() == "/delete_course") {
            std::cout << "/delete_course\n";
            Response response(admin.deleteCourse(std::stoi(request.data("id"))));
            return response;
        }
    }
    return Response(status::BadRequest);
}

std::shared_ptr<User> Handler::authorizationHandler(Request request) {
    if (request.cookie("session_id").empty()) {
        return nullptr;
    }
    try {
        return std::make_shared<User>(Session::get_user(request.cookie("session_id")));
    } catch (...) {
        return nullptr;
    }
}

Response Handler::loginHandler(Request request) {
    std::string session_id;

    if (request.path() == "/login") {
        if (request.method() == "GET") {
            return Response(user.loginPage());
        } else {
            session_id = user.signIn(request.data("username"), request.data("password"));
        }
    } else {
        if (request.method() == "GET") {
            return Response(user.registerPage());
        } else {
            session_id = user.signUp(request.dataTable());
        }
    }

    if (session_id.empty()) {
        return Response(status::Forbidden);
    } else {
        Response tmp;
        tmp.setCookie("session_id", session_id, 10);  // 10 days living cookie
        tmp.setHeader("Location", "/");
        tmp.setStatus(status::MovedPermanently);
        return tmp;
    }
}
