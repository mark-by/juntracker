#include <loader/loader.h>
#include <iostream>
#include <iterator>

int main() {
    std::string filename = "../../test/test_files/loader/loader_extends.html";
    templates::Loader loader;
    loader.load(filename);
    return 0;
}
