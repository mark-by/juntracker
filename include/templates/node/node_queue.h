#ifndef JUNTRACKER_NODE_QUEUE_H
#define JUNTRACKER_NODE_QUEUE_H

#include <node/node.h>

namespace templates {
        class NodeQueue {
            public:
            NodeQueue() {};

            explicit NodeQueue(templates::Context &context) : context(context), _result("") {};

            void render();

            std::string result();

            void push(std::unique_ptr<Node> ptr);

            bool empty();

            std::unique_ptr<Node> front();

            size_t size();

            void pop();

            void set(const std::string &buffer);

            std::unordered_map<std::string, std::unique_ptr<Node>> blocks;
            private:

            std::tuple<std::string::const_iterator, std::unique_ptr<templates::Node>>
            parse(std::string::const_iterator _start, std::string::const_iterator _end, int type);

            bool _render();

            bool renderText();

            bool renderBlock();

            std::deque<std::unique_ptr<Node>> nodes;
            Context context;
            std::string _result;
        };
};

#endif //JUNTRACKER_NODE_QUEUE_H
