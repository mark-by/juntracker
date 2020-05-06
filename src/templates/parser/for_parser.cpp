#include <parser/parser.h>

std::unique_ptr<templates::Node>templates::ForParser::parse() {
    return std::make_unique<templates::ForNode>("", "");
}

std::string templates::ForParser::getIterator() {
    return std::string();
}

std::string templates::ForParser::getVar() {
    return std::string();
}
