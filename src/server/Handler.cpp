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

std::string Handler::admin(Request request, const User& user) {
    if (request.path() == "/") {
        // Response response(admin.getMainPage(user.get_id()))
    }
    Response response("<html><h1>Hello world! (From Admin)</h1></html>");
    std::cout << request.path() << '\n';
    if (!request.data("id").empty()) {
        if (request.path() == "/student") {
            // Response response(admin.getPageStudents(std::stoi(request._data("id"))));
        }
        if (request.path() == "/getPageStudents") {
            // Response response(admin.getPageStudents(boost::lexical_cast<int>(request._data("id"))));
        }
        if (request.path() == "/getPaymentByStudent") {
            // Response response(admin.getPaymentByStudent(std::stoi(request._data("id"))));
        }
    }
    if (request.path() == "student") {
        // Response response(admin.findStudent(request._data("name")));
    }
    if (request.path() == "getStudentsBy") {
        // Response response(admin.getStudentsBy(request.dataTable));
    }
    return response.str();
}
