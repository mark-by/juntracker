#include <parser/parser.h>
#include <parser/re_tags.h>

std::unique_ptr<templates::Node>templates::TextParser::parse() {
    return std::make_unique<templates::TextNode>("", std::string(begin, end));
}

std::string::const_iterator templates::TextParser::set(std::string::const_iterator _begin, std::string::const_iterator _end) {
    begin = _begin;
    end = _end;
    return _end;
}

bool templates::TextParser::empty() {
    return begin == end;
}

