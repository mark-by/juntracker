//
// Created by gg on 15.04.2020.
//

#include "Handler.h"
#include "../database/session.h"

void Handler::choosePermission(Request request, Response& response, const User &user) {
    switch(user.permission()) {
        case Permission::admin:
            std::cout << "ADMIN" << std::endl;
            adminHandler(request, response, user);
            break;
        case Permission::teacher:
            std::cout << "TEACHER" << std::endl;
            teacherHandler(request, response, user);
            break;
        case Permission::customer:
            std::cout << "CUSTOMER" << std::endl;
            customerHandler(request, response, user);
            break;
        default:
            std::cout << "DEFAULT" << std::endl;
            response.setHeader("Location", "/login");
            response.setStatus(status::Unauthorized);
            break;
    }
}

void Handler::customerHandler(Request request, Response& response, const User &user) {
    /*if (request.path() == "/") {
        response = Response(customerApi.getMainPage(user.id()));
    } else if (request.path() == "/api/schedule") {
        response = Response(customerApi.getSchedule(user.id()));
    } else if (request.path() == "/api/rating") {
        response = Response(customerApi.getRatingPage(user.id()))
    }*/
}

void Handler::teacherHandler(Request request, Response& response, const User &user) {
    /*if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(teacherApi.getMainPage(user.id()));
        } else if (request.path() == "/api/rating") {
            response = Response(teacherApi.getRatingPage(user.id()));
        }
    } else {
        if (request.path() == "/api/save_current_lesson") {
            response = Response(teacherApi.saveCurrentLesson(request.dataTable()));
        } else if (request.path() == "/api/rate") {
            response = Response(teacherApi.rate(request.dataTable()));
        } else if (request.path() == "/api/final_marks") {
            response = Response(teacherApi.finalRate(request.dataTable()));
        }
    }*/
}

void Handler::adminHandler(Request request, Response& response, const User &user) {
    if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(adminApi.getMainPage(user.id()));
        } else if (request.path() == "/api/students") {
            response = Response(adminApi.getPageStudents(user.id()));
        } else if (request.path() == "/api/student") {
            response = Response(adminApi.findStudent(request.data("name")));
        }
    } else {
        if (request.path() == "/api/save_current_lesson") {
            response = Response(adminApi.saveCurrentLesson(request.dataTable()));
        } else if (request.path() == "/api/delete_student") {
            response = Response(adminApi.deleteStudent(std::stoi(request.data("id"))));
        } else if (request.path() == "/api/create_student") {
            response = Response(adminApi.createStudent(request.dataTable()));
        } else if (request.path() == "/api/add_course") {
            response = Response(adminApi.addCourse(request.dataTable()));
        } else if (request.path() == "/api/delete_course") {
            response = Response(adminApi.deleteCourse(std::stoi(request.data("id"))));
        }
    }
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

    if (request.path() == "/logout") {
        Response response;
        response.setCookie("session_id", "", -1000);
        Session::remove(Session::get_user(request.cookie("session_id")).id());
        response.setHeader("Location", "/login");
        response.setStatus(status::Found);
        return response;
    } else if (request.path() == "/login") {
        if (request.method() == "GET") {
            return Response(userApi.loginPage());
        } else {
            std::cout << "loginHandler signIn" << std::endl;
            session_id = userApi.signIn(request.data("username"), request.data("password"));
        }
    } else if (request.path() == "/register") {
        if (request.method() == "GET") {
            return Response(userApi.registerPage());
        } else {
            session_id = userApi.signUp(request.dataTable());
        }
    }

    if (session_id.empty()) {
        return Response(status::Forbidden);
    } else {
        Response tmp;
        tmp.setCookie("session_id", session_id, 10);  // 10 days living cookie
        tmp.setHeader("Location", "/");
        tmp.setStatus(status::Found);
        return tmp;
    }
}
