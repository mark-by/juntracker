#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node> templates::IfParser::parse() const {
    return std::make_shared<templates::IfNode>(std::string(_begin, _end),
            std::string(_startFalseBlock, _endFalseBlock),
            _statement);
}

std::string::const_iterator
templates::IfParser::set(const std::sregex_iterator &tag) {
    std::sregex_iterator none;
    auto[start, elseMatch, stop] = findScope(tag->prefix().second, tag->suffix().second);
    _statement = start->format("$3");
    _begin = start->suffix().first; // {% if isTrue %}<--
    if (elseMatch != none) {
        _end = elseMatch->prefix().second; // -->{% else %}
        _startFalseBlock = elseMatch->suffix().first;  // {% else %}<--
        _endFalseBlock = stop->prefix().second; // -->{% endif %}
    } else {
        _end = stop->prefix().second; // -->{% endif %}
    }

    return stop->suffix().first; // {% endif %}<--
}

std::tuple<std::sregex_iterator,std::sregex_iterator, std::sregex_iterator>
templates::IfParser::findScope(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::stack<std::pair<std::sregex_iterator, std::sregex_iterator>> stack;
    std::sregex_iterator currMatch(begin, end, parser::tag::anyBlock);
    std::sregex_iterator none;
    while (currMatch != none) {
        std::string currMatch_str = currMatch->str();
        int type = templates::Parser::BlockType(currMatch);
        if (type == parser::if_t) {
            stack.push({currMatch, none});
        } else if (type == parser::else_t) {
            stack.top().second = currMatch;
        } else if (type == parser::endif_t) {
            if (stack.size() == 1) {
                break;
            }
            stack.pop();
        }
        currMatch++;
    }
    return {stack.top().first, stack.top().second, currMatch};
}
