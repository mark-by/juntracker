#include <parser/parser.h>

std::unique_ptr<templates::Node>templates::TextParser::parse() {
    return std::make_unique<templates::TextNode>("", content);
}

std::unique_ptr<templates::Node>templates::VarParser::parse() {
    return std::make_unique<templates::VarNode>("", content);
}

std::string templates::VarParser::getVar() {
    return std::string();
}

std::string templates::VarParser::getProperty() {
    return std::string();
}

std::unique_ptr<templates::Node>templates::ForParser::parse() {
    return std::make_unique<templates::ForNode>("", content);
}

std::string templates::ForParser::getIterator() {
    return std::string();
}

std::string templates::ForParser::getVar() {
    return std::string();
}

std::unique_ptr<templates::Node>templates::BlockParser::parse() {
    return std::make_unique<templates::BlockNode>("", content);
}

std::string templates::BlockParser::getName() {
    return std::string();
}

std::string templates::BlockParser::getContent() {
    return std::string();
}

std::unique_ptr<templates::Node>templates::IfParser::parse() {
    return std::make_unique<templates::IfNode>("", content);
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
