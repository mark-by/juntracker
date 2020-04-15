#ifndef TEMPLATES_TEMPLATE_H
#define TEMPLATES_TEMPLATE_H
#include <context/context.h>

namespace templates {
    class Template {
    public:
        explicit Template(std::string filename) : filename(filename) {};
        std::string render(templates::Context context);
    private:
        std::string filename;
    };
}

#endif //JUNTRACKER_TEMPLATE_H
