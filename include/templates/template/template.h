#ifndef TEMPLATES_TEMPLATE_H
#define TEMPLATES_TEMPLATE_H
#include <context/context.h>
#include <parser/parser.h>
#include <node/node.h>

namespace templates {
    class Template {
    public:
        explicit Template(std::string filename) : filename(filename) {};
        std::string render(templates::Context context);
    private:
        std::string filename;
        templates::TextParser textParser;
        templates::VarParser varParser;
        templates::ForParser forParser;
        templates::IfParser ifParser;
        templates::NodeQueue nodeList;
    };
}

#endif //JUNTRACKER_TEMPLATE_H
