#ifndef TEMPLATES_PARSER_INCLUDED
#define TEMPLATES_PARSER_INCLUDED

#include <node/node.h>

#include <utility>

namespace templates {
    class Parser {
    public:
        Parser() : content(""), buffer("") {};
        virtual std::unique_ptr<templates::Node> parse() = 0;
        void init(std::string _content) {
            content = std::move(_content);
        }
    protected:
        std::string content;
        std::string buffer;
    };

    class TextParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
    };


    class VarParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
    private:
        std::string getVar();
        std::string getProperty();
    };

    class ForParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
    private:
        std::string getIterator();
        std::string getVar();
    };

    class BlockParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
    private:
        std::string getName();
        std::string getContent();
    };

    class IfParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
    private:
        std::string getStatement();
        std::string getBlockTrue();
        std::string getBlockFalse();
    };
}

#endif //TEMPLATES_PARSER_INCLUDED