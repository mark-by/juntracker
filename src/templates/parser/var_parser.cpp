#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::VarParser::parse() {
    return std::make_shared<templates::VarNode>(varName, beforeSpaces, afterSpaces);
}

std::string::const_iterator
templates::VarParser::set(const std::sregex_iterator &tag) {
    beforeSpaces = tag->format("$7");
    varName = tag->format("$8");
    afterSpaces = tag->format("$9");
    return tag->suffix().first; // {{ some.var }}<--
}
