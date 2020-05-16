#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::TextParser::parse() const {
    return std::make_shared<templates::TextNode>("", std::string(_begin, _end));
}

std::string::const_iterator templates::TextParser::set(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    _begin = begin;
    _end = end;
    return end;
}

bool templates::TextParser::empty() const {
    return _begin == _end;
}

