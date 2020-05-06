#include <parser/parser.h>

std::unique_ptr<templates::Node>templates::IfParser::parse() {
    return std::make_unique<templates::IfNode>("", "");
}

std::string templates::IfParser::getStatement() {
    return std::string();
}

std::string templates::IfParser::getBlockTrue() {
    return std::string();
}

std::string templates::IfParser::getBlockFalse() {
    return std::string();
}
