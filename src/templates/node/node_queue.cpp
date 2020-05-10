#include <node/node_queue.h>
#include <algorithm>

void templates::NodeQueue::render(templates::Context & context) {
    while (!nodes.empty()) {
        _result += nodes.front()->render(context);
        nodes.pop_front();
    }
}

void templates::NodeQueue::renderLoaded(std::unordered_map<std::string, std::shared_ptr<Node>> &blocks) {
    while (!nodes.empty()) {
        auto type = nodes.front()->type();
        switch (type) {
            case TEXTNODE:
                renderText();
                break;
            case BLOCKNODE:
                renderBlock(blocks);
                break;
            default:
                break;
        }
    }
}

void templates::NodeQueue::renderText() {
    templates::Context context;
    _result += nodes.front()->render(context);
    nodes.pop_front();
}

void templates::NodeQueue::renderBlock(std::unordered_map<std::string, std::shared_ptr<Node>> & blocks) {
    std::string blockName = nodes.front()->name();
    if (blocks[blockName]) {
        nodes.pop_front();
        nodes.push_front(std::move(blocks[blockName]));
        blocks.erase(blockName);
    }
    templates::Context context;
    _result += nodes.front()->render(context);
    nodes.pop_front();
}

std::string templates::NodeQueue::result() {
    return _result;
}

void templates::NodeQueue::push(std::shared_ptr<templates::Node> ptr) {
    nodes.push_back(std::move(ptr));
}

bool templates::NodeQueue::empty() {
    return nodes.empty();
}

std::shared_ptr<templates::Node> templates::NodeQueue::front() {
    return nodes.front();
}

size_t templates::NodeQueue::size() {
    return nodes.size();
}

void templates::NodeQueue::pop() {

}

