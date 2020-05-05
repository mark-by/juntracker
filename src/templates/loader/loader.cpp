#include <loader/loader.h>
#include <fstream>

templates::Loader::Loader(std::string filename) : filename(std::move(filename)) {}

void templates::Loader::load() {
}

void templates::Loader::merge() {

}

std::string& templates::Loader::getResult() {
    return result;
}
