#ifndef TEMPLATES_PARSER_INCLUDED
#define TEMPLATES_PARSER_INCLUDED

#include <node/node.h>
#include <node/node_queue.h>
#include <regex>

namespace templates {
    class NodeParser {
    public:
        virtual std::shared_ptr<Node> parse() const = 0;
    protected:
        std::string::const_iterator begin;
        std::string::const_iterator end;
    };

    class TextParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::string::const_iterator &_begin, const std::string::const_iterator &_end);

        bool empty() const;
    };


    class VarParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::sregex_iterator &tag);

    private:
        std::string varName;
        std::string beforeSpaces;
        std::string afterSpaces;
    };

    class ForParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::sregex_iterator &tag);

        std::tuple<std::sregex_iterator, std::sregex_iterator>
        findScope(std::string::const_iterator _begin, std::string::const_iterator _end) const;

    private:
        std::string name;
        std::string iterVar;
    };

    class BlockParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::sregex_iterator &tag);

        std::string name() const;

    private:

        std::string _name;
    };

    class IfParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::sregex_iterator &tag);

    private:
        // возвращает if else endif итераторы. else может быть пустым в случае его отсутствия
        std::tuple<std::sregex_iterator, std::sregex_iterator, std::sregex_iterator>
        findScope(std::string::const_iterator _begin, std::string::const_iterator _end) const;

        std::string statement;
        std::string::const_iterator startFalseBlock;
        std::string::const_iterator endFalseBlock;
    };

    class IncludeParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;
        std::string::const_iterator set(const std::sregex_iterator &tag);
    private:
        std::string name;
    };

    class Parser {
    public:
        Parser() = default;

        NodeQueue parse(std::string::const_iterator begin, std::string::const_iterator end);

        NodeQueue parseBlocks(std::string::const_iterator begin, std::string::const_iterator end);

        std::unordered_map<std::string, std::shared_ptr<templates::Node>>
        collectBlocks(std::string::const_iterator _begin, std::string::const_iterator _end);

        static int tagType(const std::sregex_iterator &tag);

        static int BlockType(const std::sregex_iterator &tag);

        static void clearString(std::string & str);


        std::tuple<templates::NodeQueue, std::unordered_map<std::string, std::shared_ptr<templates::Node>>>
        parseIncludes(std::string::const_iterator _begin, std::string::const_iterator _end);

    private:
        std::tuple<std::string::const_iterator, std::shared_ptr<templates::Node>>
        parseNode(const std::sregex_iterator &tag);

        BlockParser blockParser;
        TextParser textParser;
        IfParser ifParser;
        ForParser forParser;
        VarParser varParser;
        IncludeParser includeParser;
    };
}

#endif //TEMPLATES_PARSER_INCLUDED