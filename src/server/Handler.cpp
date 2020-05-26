//
// Created by gg on 15.04.2020.
//

#include "Handler.h"


std::string Handler::customerHandler(Request request, const User& user) {
    Response response("<html><h1>Hello world!(From Customer)</h1></html>");
    // Response response(customer.get(std::stoi(request._data("id"))));
    return response.str();
}

std::string Handler::teacherHandler(Request request, const User& user) {
    Response response("<html><h1>Hello world! (From Teacher)</h1></html>");
    // Response response(tutor.get(boost::lexical_cast<int>(request._data("id"))));
    return response.str();
}

std::string Handler::adminHandler(Request request, const User& user) {
    if (request.method() == "GET") {
        if (request.path() == "/") {
            std::cout << "/\n";
            Response response(admin.getMainPage(user.id()));
            return response.str();
        }

        if (!request.data("id").empty()) {
            std::cout << "id\n";
            if (request.path() == "/student") {
                std::cout << "/student\n";
                Response response(admin.getPageStudents(std::stoi(request.data("id"))));
                return response.str();
            }
            if (request.path() == "/get_page_students") {
                std::cout << "/get_page_students\n";
                Response response(admin.getPageStudents(std::stoi(request.data("id"))));
                return response.str();
            }
        }

        if (request.path() == "/student") {
            std::cout << "/student\n";
            Response response(admin.findStudent(request.data("name")));
            return response.str();
        }

    } else {
        if (request.path() == "/save_current_lesson") {
            std::cout << "/save_current_lesson\n";
            Response response(admin.saveCurrentLesson(request.dataTable()));
            return response.str();
        }

        if (request.path() == "/delete_student") {
            std::cout << "/delete_student\n";
            Response response(admin.deleteStudent(std::stoi(request.data("id"))));
            return response.str();
        }

        if (request.path() == "/create_student") {
            std::cout << "/create_student\n";
            Response response(admin.createStudent(request.dataTable()));
            return response.str();
        }

        if (request.path() == "/add_course") {
            std::cout << "/add_course\n";
            Response response(admin.addCourse(request.dataTable()));
            return response.str();
        }

        if (request.path() == "/delete_course") {
            std::cout << "/delete_course\n";
            Response response(admin.deleteCourse(std::stoi(request.data("id"))));
            return response.str();
        }
    }
}
