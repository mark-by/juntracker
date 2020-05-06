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
        void makeQueue();
        std::tuple<std::string::const_iterator, std::unique_ptr<Node>> parse(std::string::const_iterator start, int type);
        std::string _result;
        std::string buffer;
        templates::Loader loader;
        templates::TextParser textParser;
        templates::VarParser varParser;
        templates::ForParser forParser;
        templates::IfParser ifParser;
        templates::NodeQueue nodeQueue;
    };
}

#endif //JUNTRACKER_TEMPLATE_H
