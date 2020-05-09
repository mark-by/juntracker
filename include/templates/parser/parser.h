#ifndef TEMPLATES_PARSER_INCLUDED
#define TEMPLATES_PARSER_INCLUDED

#include <node/node.h>
#include <node/node_queue.h>
#include <regex>

namespace templates {
    class NodeParser {
    public:
        NodeParser() : buffer("") {};

        virtual std::unique_ptr<Node> parse() = 0;

        virtual std::string::const_iterator
        set(std::string::const_iterator _begin, std::string::const_iterator _end) = 0;

    protected:
        std::string::const_iterator begin;
        std::string::const_iterator end;
        std::string buffer;
    };

    class TextParser : public NodeParser {
    public:
        std::unique_ptr<Node> parse() override;

        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;

        bool empty();
    };


    class VarParser : public NodeParser {
    public:
        std::unique_ptr<Node> parse() override;

        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;
    };

    class ForParser : public NodeParser {
    public:
        std::unique_ptr<Node> parse() override;

        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;

        std::tuple<std::sregex_iterator, std::sregex_iterator>
        findScope(std::string::const_iterator _begin, std::string::const_iterator _end);

    private:
        static std::tuple<std::string, std::string> nameAndIterVar(const std::string &_head);

        std::string name;
        std::string iterVar;
    };

    class BlockParser : public NodeParser {
    public:
        std::unique_ptr<Node> parse() override;

        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;

        std::string name();

        static std::string getName(const std::string &text);

    private:
        std::string content();

        std::string _name;
    };

    class IfParser : public NodeParser {
    public:
        std::unique_ptr<Node> parse() override;

        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;

    private:
        std::string getStatement(const std::string &_head);

        // возвращает if else endif итераторы. else может быть пустым в случае его отсутствия
        std::tuple<std::sregex_iterator, std::sregex_iterator, std::sregex_iterator>
        findScope(std::string::const_iterator _begin, std::string::const_iterator _end);

        std::string statement;
        std::string::const_iterator startTrueBlock;
        std::string::const_iterator endTrueBlock;
        std::string::const_iterator startFalseBlock;
        std::string::const_iterator endFalseBlock;
    };

    class Parser {
    public:
        Parser() = default;

        NodeQueue parse(std::string::const_iterator begin, std::string::const_iterator end);

        static int tagType(const std::string &tag);

        static int BlockType(const std::string &text);

    private:
        std::tuple<std::string::const_iterator, std::unique_ptr<templates::Node>>
        parseNode(std::string::const_iterator _start, std::string::const_iterator _end, int type);

        BlockParser blockParser;
        TextParser textParser;
        IfParser ifParser;
        ForParser forParser;
        VarParser varParser;
    };
}

#endif //TEMPLATES_PARSER_INCLUDED