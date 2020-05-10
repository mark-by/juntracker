#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::VarParser::parse() {
    return std::make_shared<templates::VarNode>(std::string(begin, end), "");
}

std::string::const_iterator
templates::VarParser::set(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::sregex_iterator match(_begin, _end, parser::tag::variable);
    std::sregex_iterator var(match->prefix().second, match->suffix().first, parser::tag::nameWithDots);
    begin = var->prefix().second; // {{ -->some.var }}
    end = var->suffix().first; // {{ some.var<-- }}
    return match->suffix().first; // {{ some.var }}<--
}
