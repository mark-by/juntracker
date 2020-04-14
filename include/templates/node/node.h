#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <context/context.h>
//#include <utility>

namespace templates {
#define TEXTNODE 0
#define BLOCKNODE 1
#define VARNODE 2
#define FORNODE 3
#define IFNODE 4


    class Node {
    public:
        virtual std::string render(templates::Context context) = 0;

        virtual std::vector<Node*> expand() = 0;
    };


    class TextNode : public Node {
    public:
        TextNode(std::string name, std::string content) : content(std::move(content)), name(std::move(name)),
                                                          type(TEXTNODE) {};

        std::string render(templates::Context context) override;

        std::vector<Node*> expand() override;

    private:
        std::string content;
        std::string name;
        short int type;
    };

    class BlockNode : public Node {
    public:
        BlockNode(std::string name, std::string content) : content(std::move(content)), name(std::move(name)),
                                                           type(BLOCKNODE) {};

        std::string render(templates::Context context) override;

        std::vector<Node*> expand() override;

    private:
        std::string content;
        std::string name;
        short int type;
    };

    class VarNode : public Node {
    public:
        VarNode(std::string name, std::string content) : content(std::move(content)), name(std::move(name)),
                                                         type(VARNODE) {};

        std::string render(templates::Context context) override;

        std::vector<Node*> expand() override;

    private:
        std::string content;
        std::string name;
        short int type;
    };

    class ForNode : public Node {
    public:
        ForNode(std::string name, std::string content) : content(std::move(content)), name(std::move(name)),
                type(FORNODE) {};

        std::string render(templates::Context context) override;

        std::vector<Node*> expand() override;
    private:
        std::string content;
        std::string name;
        short int type;
    };

    class IfNode : public Node {
    public:
        IfNode(std::string name, std::string content) : content(std::move(content)), name(std::move(name)),
                type(IFNODE) {};

        std::string render(templates::Context context) override;

        std::vector<Node*> expand() override;
    private:
        std::string content;
        std::string name;
        short int type;
    };

}

#endif //NODE_INCLUDED