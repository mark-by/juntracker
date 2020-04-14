#include <node/node.h>

std::string templates::TextNode::render(templates::Context context) {
    return std::string();
}

std::vector<templates::Node*> templates::TextNode::expand() {
    return std::vector<templates::Node*>();
}

std::string templates::BlockNode::render(templates::Context context) {
    return std::string();
}

std::vector<templates::Node*> templates::BlockNode::expand() {
    return std::vector<templates::Node*>();
}

std::string templates::VarNode::render(templates::Context context) {
    return std::string();
}

std::vector<templates::Node*> templates::VarNode::expand() {
    return std::vector<templates::Node*>();
}

std::string templates::ForNode::render(templates::Context context) {
    return std::string();
}

std::vector<templates::Node*> templates::ForNode::expand() {
    return std::vector<templates::Node*>();
}

std::string templates::IfNode::render(templates::Context context) {
    return std::string();
}

std::vector<templates::Node*> templates::IfNode::expand() {
    return std::vector<templates::Node*>();
}
