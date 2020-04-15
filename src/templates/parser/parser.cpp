#include <parser/parser.h>

templates::Node * templates::Parser::parse() {
    return nullptr;
}

templates::Node *templates::TextParser::parse() {
    return nullptr;
}

templates::Node *templates::VarParser::parse() {
    return nullptr;
}

std::string templates::VarParser::getVar() {
    return std::string();
}

std::string templates::VarParser::getProperty() {
    return std::string();
}

templates::Node *templates::ForParser::parse() {
    return nullptr;
}

std::string templates::ForParser::getIterator() {
    return std::string();
}

std::string templates::ForParser::getVar() {
    return std::string();
}

templates::Node *templates::BlockParser::parse() {
    return nullptr;
}

std::string templates::BlockParser::getName() {
    return std::string();
}

std::string templates::BlockParser::getContent() {
    return std::string();
}

templates::Node *templates::IfParser::parse() {
    return nullptr;
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
