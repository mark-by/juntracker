#include "Handler.h"
#include "../database/session.h"

void Handler::choosePermission(Request request, Response& response, const User &user) {
    switch(user.permission()) {
        case Permission::admin:
            adminHandler(request, response, user);
            break;
        case Permission::teacher:
            teacherHandler(request, response, user);
            break;
        case Permission::customer:
            customerHandler(request, response, user);
            break;
        default:
            response.setHeader("Location", "/login");
            response.setStatus(status::Unauthorized);
            break;
    }
}

void Handler::customerHandler(Request request, Response& response, const User &user) {
    response.setStatus(status::NotFound);
    /*if (request.path() == "/") {
        response = Response(customerApi.getMainPage(user.id()));
    } else if (request.path() == "/api/schedule") {
        response = Response(customerApi.getSchedule(user.id()));
    } else if (request.path() == "/api/rating") {
        response = Response(customerApi.getRatingPage(user.id()))
    }*/
}

void Handler::teacherHandler(Request request, Response& response, const User &user) {
    response.setStatus(status::NotFound);
    if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(teacherApi.getMainPage(user));
        } else if (request.path() == "/schedule") {
            response = Response(teacherApi.schedule(user));
        }
    } else {
        if (request.path() == "/api/save_current_lesson") {
            response = Response(adminApi.saveCurrentLesson(request.dataTable()));
        }
    }
}

void Handler::adminHandler(Request request, Response& response, const User &user) {
    response.setStatus(status::NotFound);
    if (request.method() == "GET") {
        if (request.path() == "/") {
            response = Response(adminApi.getMainPage(user));
        } else if (request.path() == "/students") {
            response = Response(adminApi.getPageStudents(user));
        } else if (request.path() == "/api/user_data") {
            response = Response(adminApi.getUserData(user));
        } else if (request.path() == "/api/search_student") {
            response = Response(adminApi.searchStudent(request.data("search"), user));
        } else if (request.path() == "/schedule") {
            response = Response(adminApi.schedule(user));
        } else if (request.path() == "/api/verbose_search_student") {
            response = Response(adminApi.verboseSearchStudent(request.data("search"), user));
        } else if (request.path() == "/student") {
            response = Response(adminApi.getStudentPage(request.data("id")));
        }
    } else {
        if (request.path() == "/api/save_current_lesson") {
            response = Response(adminApi.saveCurrentLesson(request.dataTable()));
        } else if (request.path() == "/api/update_lesson") {
            response = Response(adminApi.updateLesson(request.dataTable(), user));
        } else if (request.path() == "/api/delete_student") {
            response = Response(adminApi.deleteStudents(request.dataTable(), user));
        } else if (request.path() == "/api/save_student") {
            auto json_and_code = adminApi.saveStudent(request.dataTable(), user);
            response = Response(json_and_code.second, json_and_code.first);
        } else if (request.path() == "/api/save_course") {
            response = Response(adminApi.editCourse(request.dataTable(), user));
        } else if (request.path() == "/api/delete_course") {
            response = Response(adminApi.deleteCourse(std::stoi(request.data("id"))));
        } else if (request.path() == "/api/create_lesson") {
            response = Response(adminApi.createLesson(request.dataTable(), user));
        } else if (request.path() == "/api/delete_lesson") {
            response = Response(adminApi.deleteLesson(std::stoi(request.data("id"))));
        } else if (request.path() == "/api/save_teacher") {
            response = Response(adminApi.editTeacher(request.dataTable(), user));
        } else if (request.path() == "/api/delete_teacher") {
            response = Response(adminApi.deleteTeacher(std::stoi(request.data("id"))));
        } else if (request.path() == "/api/save_cabinet") {
            response = Response(adminApi.editCabinet(request.dataTable(), user));
        } else if (request.path() == "/api/delete_cabinet") {
            response = Response(adminApi.deleteCabinet(std::stoi(request.data("id"))));
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
