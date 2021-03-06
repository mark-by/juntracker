#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <string>
#include <queue>
#include <list>
#include <utility>
#include <context/context.h>

namespace templates {
    enum TypeNode {
        TEXTNODE, BLOCKNODE, VARNODE, FORNODE, IFNODE, INCLUDENODE
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
        VarNode(std::string name, std::string beforeSpaces, std::string afterSpaces)
                : Node(std::move(name), std::move(beforeSpaces)), _afterSpaces(std::move(afterSpaces)) {
            _type = VARNODE;
        };

        std::string render(templates::Context &context) override;

    private:
        std::string _afterSpaces;
    };

    class IncludeNode : public Node {
    public:
        IncludeNode(std::string name, std::string content) : Node(std::move(name), std::move(content)) {
            _type = INCLUDENODE;
        };

        std::string render(templates::Context &context) override;
    };

    class ForNode : public Node {
    public:
        ForNode(std::string name, std::string content, std::string varName)
                : Node(std::move(name), std::move(content)),
                  _iterVar(std::move(varName)) {
            _type = FORNODE;
        };

        std::string render(templates::Context &context) override;

    private:
        std::string _iterVar;
    };

    class IfNode : public Node {
    public:
        IfNode(std::string trueBlock, std::string falseBlock, std::string statement)
                : Node(std::move(trueBlock), std::move(falseBlock)), _statement(std::move(statement)) {
            _type = IFNODE;
        };

        std::string render(templates::Context &context) override;

        std::string statement() const;

        std::tuple<std::string::const_iterator, std::string::const_iterator> trueBlock() const;

        std::tuple<std::string::const_iterator, std::string::const_iterator> falseBlock() const;

    private:
        std::string _statement;

    };

}

#endif //NODE_INCLUDED