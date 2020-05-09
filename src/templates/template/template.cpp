#include <template/template.h>

void templates::Template::render(templates::Context &context) {
    nodeQueue.set(buffer);
    nodeQueue.render();
    _result = nodeQueue.result();
}

void templates::Template::_render(templates::Context &context) {

}

templates::Template::Template(const std::string &filename) {
    loader.load(filename);
    buffer = loader.result();
}

std::string templates::Template::result() {
    return _result;
}

