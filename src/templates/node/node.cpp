#include <node/node.h>

std::string templates::TextNode::render(templates::Context &context) {
    return _content;
}

std::string templates::BlockNode::render(templates::Context &context) {
    return _content;
}

std::string templates::VarNode::render(templates::Context &context) {
    return context.get<std::string>(_name);
}

std::string templates::ForNode::render(templates::Context &context) {
    return std::string();
}

std::string templates::IfNode::render(templates::Context &context) {
    return std::string();
}

std::string templates::IfNode::getElseContent() {
    return elseContent;
}

void templates::IfNode::setElseContent(const std::string &content) {
   _content = content;
}
