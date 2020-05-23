#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::ForParser::parse() const {
    return std::make_shared<templates::ForNode>(_name, std::string(_begin, _end), _iterVar);
}

std::string::const_iterator templates::ForParser::set(const std::sregex_iterator &tag) {
    auto [startFor, endFor] = findScope(tag->prefix().second, tag->suffix().second);
    _name = startFor->format("$2");
    _iterVar = startFor->format("$3");
    _begin = startFor->suffix().first; // {% for i in array %}<--
    _end = endFor->prefix().second; //-->{% endfor %}
    return endFor->suffix().first; // {% endfor %}<--
}

std::tuple<std::sregex_iterator, std::sregex_iterator>
templates::ForParser::findScope(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::sregex_iterator forTag(begin, end, parser::tag::startForOrEndFor);
    std::sregex_iterator none;
    std::stack<std::sregex_iterator> stack;
    while (forTag != none) {
        if (!forTag->format("$1").empty()) { // значит {% for i in array %}
            stack.push(forTag);
        } else { // в другом случае это {% endfor %}
            if (stack.size() == 1) {
                break;
            }
            stack.pop();
        }
        forTag++;
    }

    return {stack.top(), forTag};
}
