#ifndef TEMPLATES_LOADER_INCLUDED
#define TEMPLATES_LOADER_INCLUDED

#include <node/node.h>
#include <parser/parser.h>
#include <map>

namespace templates {
    class Loader {
    public:

        void load(const std::string &filename);
        std::string result();

    private:
        void makeBlockTable(const std::string &text);
        void makeQueue(std::string::const_iterator _begin, std::string::const_iterator _end);

        std::string _result;
        templates::NodeQueue nodeQueue;
        templates::BlockParser blockParser;
        templates::TextParser textParser;
    };
}

#endif //TEMPLATES_LOADER_INCLUDED
