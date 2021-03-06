#ifndef JUNTRACKER_NODE_QUEUE_H
#define JUNTRACKER_NODE_QUEUE_H

#include <node/node.h>

namespace templates {
    class NodeQueue {
    public:
        NodeQueue() : _result("") {};

        void render(templates::Context & context);

        std::string result() const;

        void push(std::shared_ptr<Node> ptr);

        bool empty() const;

        std::shared_ptr<Node> front() const;

        size_t size() const;

        void pop();

        void renderLoaded(std::unordered_map<std::string, std::shared_ptr<Node>> &loaded);

    private:

        void renderText();

        void renderLoadedNode(std::unordered_map<std::string, std::shared_ptr<Node>> &loaded);

        std::deque<std::shared_ptr<Node>> _nodes;
        std::string _result;
    };
};

#endif //JUNTRACKER_NODE_QUEUE_H
