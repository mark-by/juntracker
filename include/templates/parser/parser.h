#ifndef TEMPLATES_PARSER_INCLUDED
#define TEMPLATES_PARSER_INCLUDED

#include <node/node.h>

namespace templates {
    class Parser {
    public:
        Parser(std::string content) : content(content), buffer("") {}
        templates::Node * parse();
        void init(std::string content);
    private:
        std::string getBlockName(size_t begin, size_t end);
        std::string getVarName(size_t begin, size_t end);

        std::string content;
        std::string buffer;
    };
}

#endif //TEMPLATES_PARSER_INCLUDED