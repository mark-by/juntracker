#include <template/template.h>

void templates::Template::render(templates::Context &context) {
    nodeQueue.render(context);
}

templates::Template::Template(const std::string &filename) {
    loader.load(filename);
    std::string buffer = loader.result();
    nodeQueue = parser.parse(buffer.cbegin(), buffer.cend());
}

std::string templates::Template::result() {
    return nodeQueue.result();
}

