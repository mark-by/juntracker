#include <node/node.h>
#include <node/node_queue.h>
#include <parser/parser.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/exception/exception.hpp>

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
    bool statementIsTrue;
    try {
        statementIsTrue = context.get<bool>(statement());
    } catch(const boost::property_tree::ptree_bad_data & err) {
        std::string statementStr;
        try {
            statementStr = context.get<std::string>(statement());
        } catch (const boost::property_tree::ptree_bad_data & err) {
            throw std::runtime_error(statement() + " variable cannot be recognized as a boolean value");
        }
        if (statementStr.empty() || statementStr == "0") {
            statementIsTrue = false;
        } else {
            statementIsTrue = true;
        }
    }
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

std::string templates::IncludeNode::render(templates::Context &context) {
    return std::string();
}
