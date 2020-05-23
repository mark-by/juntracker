#ifndef TEMPLATES_TEMPLATE_H
#define TEMPLATES_TEMPLATE_H
#include <context/context.h>
#include <parser/parser.h>
#include <loader/loader.h>
#include <node/node.h>
#include <tuple>

namespace templates {
    class Template {
    public:
        explicit Template(const std::string &settingsPath = "settings") : _loader(settingsPath) {};
        std::string render(templates::Context &context);
        void set(const std::string &filename);
    private:
        Parser _parser;
        Loader _loader;
    };
}

#endif //JUNTRACKER_TEMPLATE_H
