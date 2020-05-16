#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::VarParser::parse() const {
    return std::make_shared<templates::VarNode>(_varName, _beforeSpaces, _afterSpaces);
}

std::string::const_iterator
templates::VarParser::set(const std::sregex_iterator &tag) {
    _beforeSpaces = tag->format("$7");
    _varName = tag->format("$8");
    _afterSpaces = tag->format("$9");
    return tag->suffix().first; // {{ some.var }}<--
}
