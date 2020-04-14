#include <loader/loader.h>

templates::Loader::Loader(std::string filename) : filename(filename) { }

templates::NodeList templates::Loader::load() {
    return templates::NodeList();
}

templates::NodeList templates::Loader::merge(templates::NodeList & l, templates::NodeList & r) {
    return templates::NodeList();
}
