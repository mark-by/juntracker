#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::ForParser::parse() {
    return std::make_shared<templates::ForNode>(name, std::string(begin, end), iterVar);
}

std::string::const_iterator templates::ForParser::set(const std::sregex_iterator &tag) {
    auto [startFor, endFor] = findScope(tag->prefix().second, tag->suffix().second);
    name = startFor->format("$2");
    iterVar = startFor->format("$3");
    begin = startFor->suffix().first; // {% for i in array %}<--
    end = endFor->prefix().second; //-->{% endfor %}
    return endFor->suffix().first; // {% endfor %}<--
}

std::tuple<std::sregex_iterator, std::sregex_iterator>
templates::ForParser::findScope(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::sregex_iterator forTag(_begin, _end, parser::tag::startForOrEndFor);
    std::sregex_iterator end;
    std::stack<std::sregex_iterator> stack;
    while (forTag != end) {
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