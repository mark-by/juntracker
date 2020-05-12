#include <template/template.h>

std::string templates::Template::render(templates::Context &context) {
    std::string buffer = loader.result();
    auto nodeQueue = parser.parse(buffer.cbegin(), buffer.cend());
    nodeQueue.render(context);
    std::string result =  nodeQueue.result();
    templates::Parser::clearString(result);
    return result;
}

void templates::Template::set(const std::string &_filename) {
    loader.load(_filename);
}

