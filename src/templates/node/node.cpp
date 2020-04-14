#include <node/node.h>

std::string templates::TextNode::render(templates::Context context) {
    return std::string();
}

templates::NodeList templates::TextNode::expand() {
    return templates::NodeList();
}

std::string templates::BlockNode::render(templates::Context context) {
    return std::string();
}

templates::NodeList templates::BlockNode::expand() {
    return templates::NodeList();
}

std::string templates::VarNode::render(templates::Context context) {
    return std::string();
}

templates::NodeList templates::VarNode::expand() {
    return templates::NodeList();
}

std::string templates::ForNode::render(templates::Context context) {
    return std::string();
}

templates::NodeList templates::ForNode::expand() {
    return templates::NodeList();
}

std::string templates::IfNode::render(templates::Context context) {
    return std::string();
}

templates::NodeList templates::IfNode::expand() {
    return templates::NodeList();
}
