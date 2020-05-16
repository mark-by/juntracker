#include <parser/parser.h>
#include <parser/re_tags.h>
#include <boost/algorithm/string.hpp>

int templates::Parser::tagType(const std::sregex_iterator &tag) {
    if (!tag->format("$1").empty()) {
        return BlockType(tag);
    }
    if (!tag->format("$6").empty()) {
        return parser::variable_t;
    }
    if (!tag->format("$10").empty()) {
        return parser::comment_t;
    }
    return parser::undefined_t;
}

int templates::Parser::BlockType(const std::sregex_iterator &tag) {
    std::string name = tag->format("$2");
    if (name == "block") {
        return parser::block_t;
    } else if (name == "if") {
        return parser::if_t;
    } else if (name == "for") {
        return parser::for_t;
    } else if (name == "include") {
        return parser::include_t;
    } else if (name == "extends") {
        return parser::extends_t;
    } else if (name == "endfor") {
        return parser::endfor_t;
    } else if (name == "else") {
        return parser::else_t;
    } else if (name == "endif") {
        return parser::endif_t;
    } else if (name == "endblock") {
        return parser::endblock_t;
    } else {
        return parser::undefined_t;
    }
}

templates::NodeQueue templates::Parser::parse(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    templates::NodeQueue nodes;
    std::sregex_iterator currMatch(begin, end, parser::tag::any);
    std::sregex_iterator none;
    std::string::const_iterator textStart = begin;
    while (currMatch != none) {
        if (currMatch->suffix().first <= textStart) {
            currMatch++;
            continue;
        }
        auto[endBlock, node] = parseNode(currMatch);
        textParser.set(textStart, currMatch->prefix().second);
        if (!textParser.empty()) {
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

std::tuple<std::string::const_iterator, std::shared_ptr<templates::Node>>
templates::Parser::parseNode(const std::sregex_iterator &tag) {
    std::string::const_iterator endBlock;
    int type = tagType(tag);
    switch (type) {
        case parser::for_t:
            endBlock = forParser.set(tag);
            return {endBlock, forParser.parse()};
        case parser::if_t:
            endBlock = ifParser.set(tag);
            return {endBlock, ifParser.parse()};
        case parser::variable_t:
            endBlock = varParser.set(tag);
            return {endBlock, varParser.parse()};
        default:
            return {tag->suffix().first, nullptr};
    }
}

std::unordered_map<std::string, std::shared_ptr<templates::Node>>
templates::Parser::collectBlocks(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::unordered_map<std::string, std::shared_ptr<templates::Node>> blocks;
    std::sregex_iterator currStartBlock(begin, end, parser::tag::startBlock);
    std::sregex_iterator none;
    while (currStartBlock != none) {
        blockParser.set(currStartBlock);
        blocks.insert({blockParser.name(), blockParser.parse()});
        currStartBlock++;
    }
    return blocks;
}

templates::NodeQueue
templates::Parser::parseBlocks(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    templates::NodeQueue nodes;
    auto currStartBlock = std::sregex_iterator(begin, end, parser::tag::startBlock);
    std::sregex_iterator none;
    auto startText = begin;
    while (currStartBlock != none) {
        auto endBlock = blockParser.set(currStartBlock);
        textParser.set(startText, currStartBlock->prefix().second);
        nodes.push(textParser.parse());
        nodes.push(blockParser.parse());
        startText = endBlock;
        currStartBlock++;
    }
    textParser.set(startText, end);
    nodes.push(textParser.parse());
    return nodes;
}

std::tuple<templates::NodeQueue, std::unordered_map<std::string, std::shared_ptr<templates::Node>>>
templates::Parser::parseIncludes(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    templates::NodeQueue nodes;
    std::unordered_map<std::string, std::shared_ptr<templates::Node>> includes;
    std::sregex_iterator currInclude(begin, end, parser::tag::includeTag);
    std::sregex_iterator none;
    auto startText = begin;
    while (currInclude != none) {
        includes.insert({currInclude->format("$2"), nullptr});
        auto endTag = includeParser.set(currInclude);
        textParser.set(startText, currInclude->prefix().second);
        nodes.push(textParser.parse());
        nodes.push(includeParser.parse());
        startText = endTag;
        currInclude++;
    }
    textParser.set(startText, end);
    nodes.push(textParser.parse());
    return {nodes, includes};
}

void templates::Parser::clearString(std::string &str) {
    boost::trim(str);
    str = std::regex_replace(std::regex_replace(str, parser::tag::beforeHtmlTagSpaces, ""),
                             parser::tag::afterHtmlTagSpaces, "$1");
}

