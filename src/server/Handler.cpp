//
// Created by gg on 15.04.2020.
//

#include "Handler.h"
#include "../database/user.h"


std::string Handler::customer(Request request, const User& user) {
    Response response("<html><h1>Hello world!(From Customer)</h1></html>");
    // Response response(customer.get(std::stoi(request._data("id"))));
    return response.str();
}

std::string Handler::teacher(Request request, const User& user) {
    Response response("<html><h1>Hello world! (From Teacher)</h1></html>");
    // Response response(tutor.get(boost::lexical_cast<int>(request._data("id"))));
    return response.str();
}

std::string Handler::adminHandler(Request request, const User& user) {
    if (request.method() == "GET") {
        if (request.path() == "/") {
            // Response response(adminHandler.getMainPage(user.get_id()))
        }

        if (!request.data("id").empty()) {
            if (request.path() == "/student") {
                Response response(adminHandler.getPageStudents(std::stoi(request._data("id"))));
            }
            if (request.path() == "/get_page_students") {
                // Response response(adminHandler.getPageStudents(boost::lexical_cast<int>(request._data("id"))));
            }
            if (request.path() == "/getPaymentByStudent") {
                // Response response(adminHandler.getPaymentByStudent(std::stoi(request._data("id"))));
            }
        }

        if (request.path() == "/student") {
            // Response response(adminHandler.findStudent(request._data("name")));
        }

        if (request.path() == "/get_students_by") {
            // Response response(adminHandler.getStudentsBy(request.dataTable));
        }

    } else {
        if (request.path() == "/save_current_lesson") {
            // Response response(adminHandler.SaveCurrentLesson(request.dataTable));
        }

        if (request.path() == "delete_student") {
            // Response response(adminHandler.deleteStudent(std::stoi(request._data("id"))));
        }

        if (request.path() == "create_student") {
            // Response response(adminHandler.deleteStudent(request.dataTable));
        }
    }
}
