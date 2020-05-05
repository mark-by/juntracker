#include "loader/loader.h"
#include <iostream>
#include <parser/re_tags.h>
#include <iterator>

int main() {
    std::string filename = "../../test/test_files/loader/loader_extends.html";
    std::ifstream templateFile(filename, std::ifstream::in);
    char symbol;
    std::string buffer;
    while (templateFile.get(symbol)) {
        buffer.push_back(symbol);
    }
//    auto block_begin = std::sregex_iterator(buffer.begin(), buffer.end(), block);
//    auto block_end = std::sregex_iterator();
//    std::cout << std::distance(block_begin, block_end);
    auto currPos = buffer.begin();
    std::sregex_iterator currMatch(currPos, buffer.end(), parser::tag::startBlock);
    auto it = parser::getEndOfBlock(currMatch, buffer.end());
    while (it != buffer.end()) {
        std::cout << *it++;
    }
    return 0;
}
