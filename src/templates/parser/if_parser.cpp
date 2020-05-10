#include <parser/parser.h>
#include <parser/re_tags.h>

std::shared_ptr<templates::Node> templates::IfParser::parse() {
    return std::make_shared<templates::IfNode>(std::string(begin, end),
            std::string(startFalseBlock, endFalseBlock),
            statement);
}

std::string templates::IfParser::getStatement(const std::string &head) {
    std::sregex_iterator match(head.cbegin(), head.cend(), parser::tag::nameWithDots);
    match++;
    return match->str();
}

std::string::const_iterator
templates::IfParser::set(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::sregex_iterator none;
    auto[start, elseMatch, stop] = findScope(_begin, _end);
    statement = getStatement(start->str());
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
    std::stack<std::sregex_iterator> if_stack;
    std::stack<std::sregex_iterator> else_stack;
    std::sregex_iterator currMatch(_begin, _end, parser::tag::anyBlock);
    std::sregex_iterator none;
    while (currMatch != none) {
        int type = templates::Parser::BlockType(currMatch->str());
        if (type == parser::if_t) {
            if_stack.push(currMatch);
        } else if (type == parser::else_t) {
            else_stack.push(currMatch);
        } else if (type == parser::endif_t) {
            if (if_stack.size() == 1) {
                break;
            }
            if_stack.pop();
            if (!else_stack.empty()) {
                else_stack.pop();
            }
        }
        currMatch++;
    }
    if (!else_stack.empty()) {
        return {if_stack.top(), else_stack.top(), currMatch};
    } else {
        return {if_stack.top(), none, currMatch};
    }
}
