#include <parser/parser.h>

std::unique_ptr<templates::Node>templates::BlockParser::parse() {
    return std::make_unique<templates::BlockNode>(_name, content());
}

std::string templates::BlockParser::name() {
    return _name;
}

std::string templates::BlockParser::content() {
    return std::string(begin, end);
}

std::string::const_iterator templates::BlockParser::set(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::sregex_iterator startMatch(_begin, _end, parser::tag::startBlock);
    _name = parser::getName(startMatch->str());
    begin = startMatch->suffix().first; // {% block someblock %}<--
    std::sregex_iterator endMatch(_begin, _end, parser::tag::endBlock);
    end = endMatch->prefix().second; // -->{% endblock %}
    return endMatch->suffix().first; // {% endblock %}<--
}
