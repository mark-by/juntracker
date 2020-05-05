#ifndef TEMPLATES_LOADER_INCLUDED
#define TEMPLATES_LOADER_INCLUDED

#include <node/node.h>
#include <parser/parser.h>
#include <map>

namespace templates {
    class Loader {
    public:
        explicit Loader(std::string filename);

        void load();
        std::string& getResult();

    private:
        void merge();

        std::unordered_map<std::string, std::unique_ptr<Node>> blocks;
        std::string filename;
        std::string result;
        templates::NodeQueue nodeQueue;
        templates::BlockParser blockParser;
        templates::TextParser textParser;
    };
}

#endif //TEMPLATES_LOADER_INCLUDED
