#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::BlockParser::parse() {
    return std::make_shared<templates::BlockNode>(_name, content());
}

std::string templates::BlockParser::getName(const std::string &text) {
    std::sregex_iterator currentMatch(text.begin(), text.end(), parser::tag::nameWithDots);
    currentMatch++;
    return currentMatch->str();
}

std::string templates::BlockParser::name() {
    return _name;
}

std::string templates::BlockParser::content() {
    return std::string(begin, end);
}

std::string::const_iterator templates::BlockParser::set(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::sregex_iterator startMatch(_begin, _end, parser::tag::startBlock);
    _name = getName(startMatch->str());
    begin = startMatch->suffix().first; // {% block someblock %}<--
    std::sregex_iterator endMatch(_begin, _end, parser::tag::endBlock);
    end = endMatch->prefix().second; // -->{% endblock %}
    return endMatch->suffix().first; // {% endblock %}<--
}
