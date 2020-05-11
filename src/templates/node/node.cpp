#include <node/node.h>
#include <node/node_queue.h>
#include <parser/parser.h>
#include <boost/algorithm/string.hpp>

std::string templates::TextNode::render(templates::Context &context) {
    templates::Parser::clearString(_content);
    return _content;
}

std::string templates::BlockNode::render(templates::Context &context) {
    templates::Parser::clearString(_content);
    return _content;
}

std::string templates::VarNode::render(templates::Context &context) {
    return _content + context.get<std::string>(_name) + afterSpaces;
}

std::string templates::ForNode::render(templates::Context &context) {
    templates::Parser parser;
    std::string result;
    auto array = context.getObjects(iterVar); // iterVar - переменная, по которой итерируемся
    auto nodeQueue = parser.parse(_content.cbegin(), _content.cend());
    for (auto & element : array) {
        auto currentQueue = nodeQueue;
        context.set(_name, element);
        currentQueue.render(context);
        result += currentQueue.result();
    }
    return result;
}

std::string templates::IfNode::render(templates::Context &context) {
    templates::Parser parser;
    bool statementIsTrue = context.get<bool>(statement());
    templates::NodeQueue nodeQueue;
    if (statementIsTrue) {
        auto [start, stop] = trueBlock();
        nodeQueue = parser.parse(start, stop);
    } else {
        auto [start, stop] = falseBlock();
        nodeQueue = parser.parse(start, stop);
    }
    nodeQueue.render(context);
    return nodeQueue.result();
}

std::string templates::IfNode::statement() const {
    return _statement;
}

std::tuple<std::string::const_iterator, std::string::const_iterator> templates::IfNode::falseBlock() const {
    return {_content.cbegin(), _content.cend()};
}

std::tuple<std::string::const_iterator, std::string::const_iterator> templates::IfNode::trueBlock() const {
    return {_name.cbegin(), _name.cend()};
}
