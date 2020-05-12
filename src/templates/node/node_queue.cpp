#include <node/node.h>
#include <algorithm>

bool templates::NodeQueue::_render() {
    auto type = nodes.front()->type();
    switch (type) {
        case TEXTNODE:
            return renderText();
        case BLOCKNODE:
            return renderBlock();
        default:
            return false;
    }
}

bool templates::NodeQueue::renderText() {
    _result += nodes.front()->render(context);
    nodes.pop_front();
    return true;
}

bool templates::NodeQueue::renderBlock() {
    std::string blockName = nodes.front()->name();
    if (blocks[blockName]) {
        nodes.pop_front();
        nodes.push_front(std::move(blocks[blockName]));
        blocks.erase(blockName);
    }
    _result += nodes.front()->render(context);
    nodes.pop_front();
return true;
}

std::string templates::NodeQueue::result() {
    return _result;
}

void templates::NodeQueue::render() {
    while (!nodes.empty()) {
        _render();
    }
}

void templates::NodeQueue::push(std::unique_ptr<templates::Node> ptr) {
    nodes.push_back(std::move(ptr));
}

bool templates::NodeQueue::empty() {
    return nodes.empty();
}

std::unique_ptr<templates::Node> templates::NodeQueue::front() {
    return std::move(nodes.front());
}

size_t templates::NodeQueue::size() {
    return nodes.size();
}

void templates::NodeQueue::pop() {

}

