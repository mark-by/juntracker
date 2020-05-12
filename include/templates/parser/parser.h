#ifndef TEMPLATES_PARSER_INCLUDED
#define TEMPLATES_PARSER_INCLUDED

#include <node/node.h>
#include <parser/re_tags.h>
#include <utility>

namespace templates {
    class Parser {
    public:
        Parser() : buffer("") {};
        virtual std::unique_ptr<templates::Node> parse() = 0;
        virtual std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) = 0;
    protected:
        std::string::const_iterator begin;
        std::string::const_iterator end;
        std::string buffer;
    };

    class TextParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;
    };


    class VarParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;
    private:
        std::string getVar();
        std::string getProperty();
    };

    class ForParser: public Parser {
    public:
        std::unique_ptr<templates::Node> parse() override;
        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;
    private:
        std::string getIterator();
        std::string getVar();
    };

    class BlockParser: public Parser {
   public:
        std::unique_ptr<templates::Node> parse() override;
        std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;
        std::string name();
    private:
        std::string content();
        std::string _name;
    };

    class IfParser: public Parser {
    public:
       std::unique_ptr<templates::Node> parse() override;
       std::string::const_iterator set(std::string::const_iterator _begin, std::string::const_iterator _end) override;
    private:
        std::string getStatement();
        std::string getBlockTrue();
        std::string getBlockFalse();
    };
}

#endif //TEMPLATES_PARSER_INCLUDED