#include <parser/parser.h>

templates::Node * templates::Parser::parse() {
    return nullptr;
}

void templates::Parser::init(std::string initContent) {
    content = initContent;
}

std::string templates::Parser::getBlockName(size_t begin, size_t end) {
    return std::string();
}

std::string templates::Parser::getVarName(size_t begin, size_t end) {
    return std::string();
}