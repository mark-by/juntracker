#include <template/template.h>

std::string templates::Template::render(templates::Context &context) {
    std::string buffer = _loader.result();
    auto nodeQueue = _parser.parse(buffer.cbegin(), buffer.cend());
    nodeQueue.render(context);
    return nodeQueue.result();
}

void templates::Template::set(const std::string &_filename) {
    _loader.load(_filename);
}

