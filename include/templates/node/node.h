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
        Node(std::string name, std::string content) : content(std::move(content)), name(std::move(name)) {}

        virtual std::string render(templates::Context context) = 0;

        virtual templates::NodeQueue expand() = 0;

        std::string getContent() const { return content; }

        std::string getName() const { return name; }

        short int getType() const { return type; }

    protected:
        std::string content;
        std::string name;
        short int type;
    };


    class TextNode : public Node {
    public:
        TextNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            type = TEXTNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class BlockNode : public Node {
    public:
        BlockNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            type = BLOCKNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class VarNode : public Node {
    public:
        VarNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            type = VARNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class ForNode : public Node {
    public:
        ForNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            type = FORNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class IfNode : public Node {
    public:
        IfNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            type = IFNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;

        std::string getElseContent();

        void setElseContent(std::string _content);

    private:
        std::string elseContent;
    };


    class NodeQueue {
    public:
        NodeQueue() : result("") {};

        explicit NodeQueue(templates::Context context) : context(std::move(context)), result("") {};

        bool render();

        std::string renderAll();

        std::string getResult();

        void push(std::unique_ptr<Node> ptr);

        bool empty();

        std::unique_ptr<Node> front();

        size_t size();

        void pop();


    private:
        std::queue<std::unique_ptr<Node>> nodes;
        templates::Context context;
        std::string result;
    };
}

#endif //NODE_INCLUDED