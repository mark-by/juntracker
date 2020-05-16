#include <node/node_queue.h>
#include <algorithm>

void templates::NodeQueue::render(templates::Context & context) {
    while (!_nodes.empty()) {
        _result += _nodes.front()->render(context);
        _nodes.pop_front();
    }
}

void templates::NodeQueue::renderLoaded(std::unordered_map<std::string, std::shared_ptr<Node>> &loaded) {
    while (!_nodes.empty()) {
        auto type = _nodes.front()->type();
        if (type == TEXTNODE) {
            renderText();
        } else {
            renderLoadedNode(loaded);
        }
    }
}

void templates::NodeQueue::renderText() {
    templates::Context context;
    _result += _nodes.front()->render(context);
    _nodes.pop_front();
}

void templates::NodeQueue::renderLoadedNode(std::unordered_map<std::string, std::shared_ptr<Node>> & loaded) {
    std::string TagName = _nodes.front()->name();
    templates::Context context;
    if (loaded[TagName]) {
        _result += loaded[TagName]->render(context);
    } else {
        _result += _nodes.front()->render(context);
    }
    _nodes.pop_front();
}

std::string templates::NodeQueue::result() const {
    return _result;
}

void templates::NodeQueue::push(std::shared_ptr<templates::Node> ptr) {
    _nodes.push_back(std::move(ptr));
}

bool templates::NodeQueue::empty() const {
    return _nodes.empty();
}

std::shared_ptr<templates::Node> templates::NodeQueue::front() const {
    return _nodes.front();
}

size_t templates::NodeQueue::size() const {
    return _nodes.size();
}

void templates::NodeQueue::pop() {
    _nodes.pop_front();
}

