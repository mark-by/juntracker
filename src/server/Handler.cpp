//
// Created by gg on 15.04.2020.
//

#include "Handler.h"
#include "../database/session.h"


Response Handler::customerHandler(Request request) {
    Response response(status::BadRequest);
    /*if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(teacherApi.getMainPage());
        }

        if (request.path() == "/courses") {
            response = Response(teacherApi.getCoursePage());
        }
    } else {
        if (request.path() == "/course") {
            response = Response(teacherApi.courseInformation(request.dataTable()));
        }
    }*/

    return response;
}

Response Handler::teacherHandler(Request request, const User &user) {
    Response response(status::BadRequest);
    /*if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(teacherApi.getMainPage(user.id()));
        }

        if (request.path() == "/teacher/rating") {
            response = Response(teacherApi.getRatingPage(user.id()));
        }
    } else {
        if (request.path() == "/teacher/save_current_lesson") {
            response = Response(teacherApi.saveCurrentLesson(request.dataTable()));
        }

        if (request.path() == "/teacher/rate") {
            response = Response(teacherApi.rate(request.dataTable()));
        }

        if (request.path() == "/teacher/final_marks") {
            response = Response(teacherApi.finalRate(request.dataTable()));
        }
    }*/

    return response;
}

Response Handler::adminHandler(Request request, const User &user) {
    Response response(status::BadRequest);
    if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(adminApi.getMainPage(user.id()));
        }

        if (request.path() == "/api/students") {
            response = Response(adminApi.getPageStudents(user.id()));
        }

        if (request.path() == "/api/student") {
            response = Response(adminApi.findStudent(request.data("name")));
        }
    } else {
        if (request.path() == "/api/save_current_lesson") {
            response = Response(adminApi.saveCurrentLesson(request.dataTable()));
        }

        if (request.path() == "/api/delete_student") {
            response = Response(adminApi.deleteStudent(std::stoi(request.data("id"))));
        }

        if (request.path() == "/api/create_student") {
            response = Response(adminApi.createStudent(request.dataTable()));
        }

        if (request.path() == "/api/add_course") {
            response = Response(adminApi.addCourse(request.dataTable()));
        }

        if (request.path() == "/api/delete_course") {
            response = Response(adminApi.deleteCourse(std::stoi(request.data("id"))));
        }
    }

    return response;
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
        response.setCookie("session_id", "",-1000);
        Session::remove(Session::get_user(request.cookie("session_id")).id());
        response.setHeader("Location", "/login");
        response.setStatus(status::Found);
        return response;
    }

    if (request.path() == "/login") {
        if (request.method() == "GET") {
            return Response(userApi.loginPage());
        } else {
            std::cout << "loginHandler signIn" << std::endl;
            session_id = userApi.signIn(request.data("username"), request.data("password"));
        }
    } else {
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
