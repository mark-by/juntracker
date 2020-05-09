//#include <loader/loader.h>
#include <iostream>
#include <parser/re_tags.h>
#include <parser/parser.h>
#include <loader/loader.h>

int main() {
    std::string filename = "../../test/templates_test/test_files/loader/loader_extends.html";
    templates::Loader loader;
    templates::Parser parser;
    loader.load(filename);
    std::cout << loader.result() << std::endl;
    std::string result = loader.result();
    auto nodeQ = parser.parse(result.cbegin(), result.cend());
    return 0;
}
