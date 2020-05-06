#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <string>
#include <queue>
#include <list>
#include <utility>
#include <context/context.h>

namespace templates {
    enum TypeNode {
        TEXTNODE, BLOCKNODE, VARNODE, FORNODE, IFNODE
    };

    class NodeQueue;

    class Node {
    public:
        Node(std::string name, std::string content) : _content(std::move(content)), _name(std::move(name)) {}

        virtual std::string render(templates::Context &context) = 0;

        virtual templates::NodeQueue expand() = 0;

        std::string content() const { return _content; }

        std::string name() const { return _name; }

        short int type() const { return _type; }

    protected:

        std::string _content;
        std::string _name;
        short int _type;
    };


    class TextNode : public Node {
    public:
        TextNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = TEXTNODE;
        };

        std::string render(templates::Context &context) override;

        templates::NodeQueue expand() override;
    };

    class BlockNode : public Node {
    public:
        BlockNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = BLOCKNODE;
        };

        std::string render(templates::Context &context) override;

        templates::NodeQueue expand() override;
    };

    class VarNode : public Node {
    public:
        VarNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = VARNODE;
        };

        std::string render(templates::Context &context) override;

        templates::NodeQueue expand() override;
    };

    class ForNode : public Node {
    public:
        ForNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = FORNODE;
        };

        std::string render(templates::Context &context) override;

        templates::NodeQueue expand() override;
    };

    class IfNode : public Node {
    public:
        IfNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = IFNODE;
        };

        std::string render(templates::Context &context) override;

        templates::NodeQueue expand() override;

        std::string getElseContent();

        void setElseContent(const std::string & _content);

    private:
        std::string elseContent;
    };


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

        std::unordered_map<std::string, std::unique_ptr<Node>> blocks;
    private:

        bool _render();

        bool renderText();

        bool renderBlock();


        std::deque<std::unique_ptr<Node>> nodes;
        templates::Context context;
        std::string _result;
    };
}

#endif //NODE_INCLUDED