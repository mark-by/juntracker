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

    class Node {
    public:
        Node(std::string name, std::string content) : _content(std::move(content)), _name(std::move(name)) {}

        virtual std::string render(templates::Context &context) = 0;

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
    };

    class BlockNode : public Node {
    public:
        BlockNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = BLOCKNODE;
        };

        std::string render(templates::Context &context) override;
    };

    class VarNode : public Node {
    public:
        VarNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = VARNODE;
        };

        std::string render(templates::Context &context) override;
    };

    class ForNode : public Node {
    public:
        ForNode(std::string name, std::string content, std::string varName)
                : Node(std::move(name), std::move(content)),
                  iterVar(std::move(varName)) {
            _type = FORNODE;
        };

        std::string render(templates::Context &context) override;

    private:
        std::string iterVar;
    };

    class IfNode : public Node {
    public:
        IfNode(std::string name, std::string content, std::string elseContent)
        : Node(std::move(name), std::move(content)), elseContent(std::move(elseContent)) {
            _type = IFNODE;
        };

        std::string render(templates::Context &context) override;

        std::string getElseContent();

        void setElseContent(const std::string &_content);

    private:
        std::string elseContent;
    };

}

#endif //NODE_INCLUDED