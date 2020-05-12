#include <node/node_queue.h>
#include <algorithm>

void templates::NodeQueue::render(templates::Context & context) {
    while (!nodes.empty()) {
        _result += nodes.front()->render(context);
        nodes.pop_front();
    }
}

void templates::NodeQueue::renderLoaded(std::unordered_map<std::string, std::shared_ptr<Node>> &loaded) {
    while (!nodes.empty()) {
        auto type = nodes.front()->type();
        if (type == TEXTNODE) {
            renderText();
        } else {
            renderLoadedNode(loaded);
        }
    }
}

void templates::NodeQueue::renderText() {
    templates::Context context;
    _result += nodes.front()->render(context);
    nodes.pop_front();
}

void templates::NodeQueue::renderLoadedNode(std::unordered_map<std::string, std::shared_ptr<Node>> & loaded) {
    std::string TagName = nodes.front()->name();
    templates::Context context;
    if (loaded[TagName]) {
        _result += loaded[TagName]->render(context);
    } else {
        _result += nodes.front()->render(context);
    }
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

