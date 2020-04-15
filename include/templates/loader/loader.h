#ifndef TEMPLATES_LOADER_INCLUDED
#define TEMPLATES_LOADER_INCLUDED

#include <node/node.h>
#include <node/node_list.h>
#include <parser/parser.h>

namespace templates {
    class Loader {
    public:
        explicit Loader(std::string filename);

        void load();
        std::string getResult();

    private:
        templates::NodeList merge(templates::NodeList &l, templates::NodeList &r);

        std::string filename;
        std::string result;
    };
}

#endif //TEMPLATES_LOADER_INCLUDED
