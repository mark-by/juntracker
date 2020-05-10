#ifndef TEMPLATES_LOADER_INCLUDED
#define TEMPLATES_LOADER_INCLUDED

#include <node/node.h>
#include <parser/parser.h>

namespace templates {
    class Loader {
    public:

        void load(const std::string &filename);
        std::string result();

    private:
        std::string _result;
        templates::Parser parser;
    };
}

#endif //TEMPLATES_LOADER_INCLUDED
