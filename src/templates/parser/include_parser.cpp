#include <parser/parser.h>
#include <parser/re_tags.h>


std::shared_ptr<templates::Node>templates::IncludeParser::parse() const {
    return std::make_shared<templates::IncludeNode>(name, "");
}

std::string::const_iterator templates::IncludeParser::set(const std::sregex_iterator &tag) {
    name = tag->format("$2");
    return tag->suffix().first; // {% endblock %}<--
}
