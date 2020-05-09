#include <parser/parser.h>
#include <parser/re_tags.h>

std::unique_ptr<templates::Node> templates::IfParser::parse() {
    return std::make_unique<templates::IfNode>(statement, std::string(startTrueBlock, endTrueBlock),
                                               std::string(startFalseBlock, endFalseBlock));
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
    startTrueBlock = start->suffix().first; // {% if isTrue %}<--
    if (elseMatch != none) {
        endTrueBlock = elseMatch->prefix().second; // -->{% else %}
        startFalseBlock = elseMatch->suffix().first;  // {% else %}<--
        endFalseBlock = stop->prefix().second; // -->{% endif %}
    } else {
        endTrueBlock = stop->prefix().second; // -->{% endif %}
    }

    return stop->suffix().first; // {% endif %}<--
}

std::tuple<std::sregex_iterator,std::sregex_iterator, std::sregex_iterator>
templates::IfParser::findScope(std::string::const_iterator _begin, std::string::const_iterator _end) {
    std::stack<std::sregex_iterator> if_stack;
    std::stack<std::sregex_iterator> else_stack;
    std::sregex_iterator currMatch(_begin, _end, parser::tag::anyBlock);
    std::sregex_iterator end;
    while (currMatch != end) {
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
        end = else_stack.top();
    }
    return {if_stack.top(), end, currMatch};
}
