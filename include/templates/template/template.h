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
        explicit Template(const std::string &settingsPath = "settings") : loader(settingsPath) {};
        std::string render(templates::Context &context);
        void set(const std::string &filename);
    private:
        Parser parser;
        Loader loader;
    };
}

#endif //JUNTRACKER_TEMPLATE_H
