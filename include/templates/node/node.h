#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <string>
#include <context/context.h>
#include <list>
#include <utility>

namespace templates {
#define NODE -1
#define TEXTNODE 0
#define BLOCKNODE 1
#define VARNODE 2
#define FORNODE 3
#define IFNODE 4

    class NodeList;

    class Node {
    public:
        explicit Node(std::string name = "", std::string content = "") : name(std::move(name)),
                                                                         content(std::move(content)) {}

        virtual std::string render(templates::Context context) = 0;

        virtual templates::NodeList expand() = 0;

    protected:
        short int type;
        std::string name;
        std::string content;
    };

    class NodeList : public std::list<Node> {
    public:
        std::string render();

        bool isEmtpy();

    private:
        templates::Context context;
    };

    class TextNode : public Node {
    public:
        TextNode(std::string name, std::string content) : Node(name, content), type(TEXTNODE){};

        std::string render(templates::Context context) override;

        templates::NodeList expand() override;
    private:
        using Node::type;
        using Node::name;
        using Node::content;
    };

    class BlockNode : public Node {
    public:
        BlockNode() : type(BLOCKNODE), content("") {};

        std::string render(templates::Context context) override;

        templates::NodeList expand() override;
    };

    class VarNode : public Node {
    public:
        VarNode() : type(VARNODE), content("") {};

        std::string render(templates::Context context) override;

        templates::NodeList expand() override;
    };

    class ForNode : public Node {
    public:
        ForNode() : type(FORNODE), content("") {};

        std::string render(templates::Context context) override;

        templates::NodeList expand() override;
    };

    class IfNode : public Node {
    public:
        IfNode() : type(IFNODE), content("") {};

        std::string render(templates::Context context) override;

        templates::NodeList expand() override;
    };

}

#endif //NODE_INCLUDED