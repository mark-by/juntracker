#ifndef TEMPLATES_LOADER_INCLUDED
#define TEMPLATES_LOADER_INCLUDED

#include <node/node.h>
#include <node/node_list.h>

namespace templates {
    class Loader {
    public:
        explicit Loader(std::string filename);

        templates::NodeList load();

    private:
        templates::NodeList merge(templates::NodeList &l, templates::NodeList &r);

        std::string filename;

    };
}

#endif //TEMPLATES_LOADER_INCLUDED
