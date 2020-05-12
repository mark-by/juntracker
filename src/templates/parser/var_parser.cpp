#include <parser/parser.h>

std::unique_ptr<templates::Node>templates::VarParser::parse() {
    return std::make_unique<templates::VarNode>("", "");
}

std::string templates::VarParser::getVar() {
    return std::string();
}

std::string templates::VarParser::getProperty() {
    return std::string();
}
