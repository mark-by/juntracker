#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node>templates::ForParser::parse() {
    return std::make_shared<templates::ForNode>(name, std::string(begin, end), iterVar);
}

std::tuple<std::string, std::string> templates::ForParser::nameAndIterVar(const std::string &_head) {
    std::sregex_iterator currMatch(_head.cbegin(), _head.cend(), parser::tag::nameWithDots);
    std::sregex_iterator end;
    std::vector<std::string> resultMatches;
    resultMatches.reserve(2);
    while (currMatch != end) {
        if (resultMatches.size() >= 2) {
            break;
        }
        std::string match = currMatch->str();
        if (match != "for" && match != "in") {
            resultMatches.push_back(match);
        }
        currMatch++;
    }
    return {resultMatches[0], resultMatches[1]};
}

std::string::const_iterator templates::ForParser::set(std::string::const_iterator _begin, std::string::const_iterator _end) {
    auto [startFor, endFor] = findScope(_begin, _end);
    auto [_name, _iterVar] = nameAndIterVar(startFor->str());
    name = _name;
    iterVar = _iterVar;
    begin = startFor->suffix().first; // {% for i in array %}<--
    end = endFor->prefix().second; //-->{% endfor %}
    return endFor->suffix().first; // {% endfor %}<--
}

std::tuple<std::sregex_iterator, std::sregex_iterator>
templates::ForParser::findScope(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::sregex_iterator startTag(_begin, _end, parser::tag::startFor);
    std::sregex_iterator end;
    std::stack<std::sregex_iterator> stack;
    while (startTag != end) {
        stack.push(startTag);
        startTag++;
    }
    std::sregex_iterator endTag(_begin, _end, parser::tag::endFor);
    std::string endTag_str = endTag->str();
    while (endTag != end) {
        if (stack.size() == 1) {
            break;
        }
        stack.pop();
        endTag++;
        endTag_str = endTag->str();
    }
    return {stack.top(), endTag};
}
