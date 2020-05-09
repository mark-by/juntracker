#include <parser/parser.h>
#include <parser/re_tags.h>

int templates::Parser::tagType(const std::string &tag) {
    switch (tag[1]) {
        case '{':
            return parser::variable_t;
        case '#':
            return parser::comment_t;
        case '%':
            return BlockType(tag);
        default:
            return parser::undefined_t;
    }
}

int templates::Parser::BlockType(const std::string &text) {
    std::smatch match;
    std::regex_search(text, match, parser::tag::name);
    std::string matchStr = match.str();

    if (matchStr == "block") {
        return parser::block_t;
    } else if (matchStr == "if") {
        return parser::if_t;
    } else if (matchStr == "for") {
        return parser::for_t;
    } else if (matchStr == "include") {
        return parser::include_t;
    } else if (matchStr == "extends") {
        return parser::extends_t;
    } else if (matchStr == "endfor") {
        return parser::endfor_t;
    } else if (matchStr == "else") {
        return parser::else_t;
    } else if (matchStr == "endif") {
        return parser::endif_t;
    } else if (matchStr == "endblock") {
        return parser::endblock_t;
    } else {
        return parser::undefined_t;
    }
}

templates::NodeQueue templates::Parser::parse(std::string::const_iterator begin, std::string::const_iterator end) {
    templates::NodeQueue nodes;
    std::sregex_iterator currMatch(begin, end, parser::tag::any);
    std::sregex_iterator none;
    std::string::const_iterator textStart = begin;
    std::string::const_iterator textEnd;
    while (currMatch != none) {
        std::string currMatch_str = currMatch->str();
        if (currMatch->suffix().first <= textStart) {
            currMatch++;
            continue;
        }
        auto [endBlock, node] = parseNode(currMatch->prefix().second, end, tagType(currMatch->str()));
        textParser.set(textStart, currMatch->prefix().second);
        if (!textParser.empty()){
            nodes.push(textParser.parse());
        }
        nodes.push(std::move(node));

        textStart = endBlock;
        currMatch++;
    }
    textParser.set(textStart, end);
    nodes.push(textParser.parse());
    return nodes;
}

std::tuple<std::string::const_iterator, std::unique_ptr<templates::Node>> templates::Parser::parseNode(std::string::const_iterator _start, std::string::const_iterator _end, int type) {
    std::string::const_iterator endBlock;
    switch(type) {
        case parser::for_t:
            endBlock = forParser.set(_start, _end);
            return std::make_tuple(endBlock, forParser.parse());
        case parser::if_t:
            endBlock = ifParser.set(_start, _end);
            return std::make_tuple(endBlock, ifParser.parse());
        case parser::variable_t:
            endBlock = varParser.set(_start, _end);
            return std::make_tuple(endBlock, varParser.parse());
        default:
            return std::make_tuple(_start, nullptr);
    }
}
