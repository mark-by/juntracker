#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <string>
#include <queue>
#include <list>
#include <context/context.h>

namespace templates {
#define TEXTNODE 0
#define BLOCKNODE 1
#define VARNODE 2
#define FORNODE 3
#define IFNODE 4

    class NodeQueue;

    class Node {
    public:
        Node(std::string name, std::string content) : content(content), name(name) {}

        virtual std::string render(templates::Context context) = 0;

        virtual templates::NodeQueue expand() = 0;

        std::string get_content() { return content; }

        std::string get_name() { return name; }

        short int get_type() { return type; }

    protected:
        std::string content;
        std::string name;
        short int type;
    };


    class TextNode : public Node {
    public:
        TextNode(std::string name, std::string content) : Node(name, content) {
            type = TEXTNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class BlockNode : public Node {
    public:
        BlockNode(std::string name, std::string content) : Node(name, content) {
            type = BLOCKNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class VarNode : public Node {
    public:
        VarNode(std::string name, std::string content) : Node(name, content) {
            type = VARNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class ForNode : public Node {
    public:
        ForNode(std::string name, std::string content) : Node(name, content) {
            type = FORNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };

    class IfNode : public Node {
    public:
        IfNode(std::string name, std::string content) : Node(name, content) {
            type = IFNODE;
        };

        std::string render(templates::Context context) override;

        templates::NodeQueue expand() override;
    };


    class NodeQueue : public std::queue<std::unique_ptr<Node>> {
    public:
        NodeQueue() : result("") {};
        explicit NodeQueue(templates::Context context): context(std::move(context)), result("") {};
        bool render();
        std::string renderAll();

        std::string getResult();

    private:
        templates::Context context;
        std::string result;
    };
}

#endif //NODE_INCLUDED