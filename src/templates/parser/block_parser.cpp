#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::BlockParser::parse() {
    return std::make_shared<templates::BlockNode>(_name, std::string(begin, end));
}

std::string templates::BlockParser::name() {
    return _name;
}

std::string::const_iterator templates::BlockParser::set(const std::sregex_iterator &tag) {
    _name = tag->format("$3");
    begin = tag->suffix().first; // {% block someblock %}<--
    std::sregex_iterator endMatch(begin, tag->suffix().second, parser::tag::endBlock);
    end = endMatch->prefix().second; // -->{% endblock %}
    return endMatch->suffix().first; // {% endblock %}<--
}
