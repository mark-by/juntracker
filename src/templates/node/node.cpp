#include <node/node.h>

#include <utility>

std::string templates::TextNode::render(templates::Context &context) {
    return _content;
}

templates::NodeQueue templates::TextNode::expand() {
    return templates::NodeQueue();
}

std::string templates::BlockNode::render(templates::Context &context) {
    return _content;
}

templates::NodeQueue templates::BlockNode::expand() {
    return templates::NodeQueue();
}

std::string templates::VarNode::render(templates::Context &context) {
    return context.get<std::string>(_name);
}

templates::NodeQueue templates::VarNode::expand() {
    return templates::NodeQueue();
}

std::string templates::ForNode::render(templates::Context &context) {
    return std::string();
}

templates::NodeQueue templates::ForNode::expand() {
    return templates::NodeQueue();
}

std::string templates::IfNode::render(templates::Context &context) {
    return std::string();
}

templates::NodeQueue templates::IfNode::expand() {
    return templates::NodeQueue();
}

std::string templates::IfNode::getElseContent() {
    return elseContent;
}

void templates::IfNode::setElseContent(const std::string &content) {
   _content = content;
}
