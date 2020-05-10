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
        explicit Template(const std::string &filename);
        void render(templates::Context &context);
        std::string result();
    private:
        void _render(templates::Context &context);
        templates::Parser parser;
        templates::Loader loader;
        templates::NodeQueue nodeQueue;
    };
}

#endif //JUNTRACKER_TEMPLATE_H
