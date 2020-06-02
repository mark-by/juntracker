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
        std::string::const_iterator _begin;
        std::string::const_iterator _end;
    };

    class TextParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::string::const_iterator &begin, const std::string::const_iterator &end);

        bool empty() const;
    };


    class VarParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::sregex_iterator &tag);

    private:
        std::string _varName;
        std::string _beforeSpaces;
        std::string _afterSpaces;
    };

    class ForParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;

        std::string::const_iterator set(const std::sregex_iterator &tag);

        static std::tuple<std::sregex_iterator, std::sregex_iterator>
        findScope(const std::string::const_iterator &begin, const std::string::const_iterator &end) ;

    private:
        std::string _name;
        std::string _iterVar;
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
        static std::tuple<std::sregex_iterator, std::sregex_iterator, std::sregex_iterator>
        findScope(const std::string::const_iterator &begin, const std::string::const_iterator &end) ;

        std::string _statement;
        std::string _falseBlock;
    };

    class IncludeParser : public NodeParser {
    public:
        std::shared_ptr<Node> parse() const override;
        std::string::const_iterator set(const std::sregex_iterator &tag);
    private:
        std::string _name;
    };

    class Parser {
    public:
        Parser() = default;

        NodeQueue parse(const std::string::const_iterator &begin, const std::string::const_iterator &end);

        NodeQueue parseBlocks(const std::string::const_iterator &begin, const std::string::const_iterator &end);

        std::unordered_map<std::string, std::shared_ptr<templates::Node>>
        collectBlocks(const std::string::const_iterator &begin, const std::string::const_iterator &end);

        static int tagType(const std::sregex_iterator &tag);

        static int BlockType(const std::sregex_iterator &tag);

        static void clearString(std::string & str);


        std::tuple<templates::NodeQueue, std::unordered_map<std::string, std::shared_ptr<templates::Node>>>
        parseIncludes(const std::string::const_iterator &begin, const std::string::const_iterator &end);

    private:
        std::tuple<std::string::const_iterator, std::shared_ptr<templates::Node>>
        parseNode(const std::sregex_iterator &tag);

        BlockParser _blockParser;
        TextParser _textParser;
        IfParser _ifParser;
        ForParser _forParser;
        VarParser _varParser;
        IncludeParser _includeParser;
    };
}

#endif //TEMPLATES_PARSER_INCLUDED