#include <loader/loader.h>

templates::Loader::Loader(std::string filename) : filename(filename) {}

void templates::Loader::load() {
}

templates::NodeList templates::Loader::merge(templates::NodeList & l, templates::NodeList & r) {
    return templates::NodeList();
}

std::string templates::Loader::getResult() {
    return std::string();
}
