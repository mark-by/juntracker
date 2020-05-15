#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node> templates::IfParser::parse() {
    return std::make_shared<templates::IfNode>(std::string(begin, end),
            std::string(startFalseBlock, endFalseBlock),
            statement);
}

std::string::const_iterator
templates::IfParser::set(const std::sregex_iterator &tag) {
    std::sregex_iterator none;
    auto[start, elseMatch, stop] = findScope(tag->prefix().second, tag->suffix().second);
    statement = start->format("$3");
    begin = start->suffix().first; // {% if isTrue %}<--
    if (elseMatch != none) {
        end = elseMatch->prefix().second; // -->{% else %}
        startFalseBlock = elseMatch->suffix().first;  // {% else %}<--
        endFalseBlock = stop->prefix().second; // -->{% endif %}
    } else {
        end = stop->prefix().second; // -->{% endif %}
    }

    return stop->suffix().first; // {% endif %}<--
}

std::tuple<std::sregex_iterator,std::sregex_iterator, std::sregex_iterator>
templates::IfParser::findScope(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::stack<std::pair<std::sregex_iterator, std::sregex_iterator>> stack;
    std::sregex_iterator currMatch(_begin, _end, parser::tag::anyBlock);
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
