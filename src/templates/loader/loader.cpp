#include <loader/loader.h>

templates::Loader::Loader(std::string filename) : filename(filename) {}

void templates::Loader::load() {
}

void templates::Loader::merge() {

}

std::string& templates::Loader::getResult() {
    return result;
}
