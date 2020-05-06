#include <loader/loader.h>
#include <fstream>
#include <parser/re_tags.h>
#include <sys/mman.h>
#include <boost/filesystem.hpp>
#include <fcntl.h>
#include <iostream>

void templates::Loader::load(const std::string &filename) {
    boost::filesystem::path filePath(filename);
    std::smatch match;
    int fd = open(filePath.c_str(), O_RDONLY);
    size_t fileSize = boost::filesystem::file_size(filename);
    std::string file((char *) mmap(nullptr, fileSize, PROT_READ,
                                   MAP_FILE | MAP_SHARED, fd, 0), fileSize);

    if (!std::regex_search(file, match, parser::tag::extends)) {
        _result = std::move(file);
        return;
    }

    std::string extendFileName = parser::getName(match.str());
    boost::filesystem::path extendPath = filePath.branch_path().append(extendFileName);
    close(fd);
    fd = open(extendPath.c_str(), O_RDONLY);
    size_t extendFileSize = boost::filesystem::file_size(extendPath);
    std::string extendFile((char *) mmap(nullptr, extendFileSize, PROT_READ,
                                   MAP_FILE | MAP_SHARED, fd, 0), extendFileSize);

    makeBlockTable(match.suffix().str());
    makeQueue(extendFile.cbegin(), extendFile.cend());
    nodeQueue.render();
    _result = nodeQueue.result();
}

std::string templates::Loader::result() {
    return _result;
}

void templates::Loader::makeBlockTable(const std::string &text) {
    auto currStartBlock = std::sregex_iterator(text.begin(), text.end(), parser::tag::startBlock);
    std::sregex_iterator end;
    while (currStartBlock != end) {
        blockParser.set(currStartBlock->prefix().second, text.cend());
        nodeQueue.blocks.insert({blockParser.name(), blockParser.parse()});
        currStartBlock++;
    }
}

void templates::Loader::makeQueue(std::string::const_iterator _begin, std::string::const_iterator _end) {
    auto currStartBlock = std::sregex_iterator(_begin, _end, parser::tag::startBlock);
    std::sregex_iterator end;
    auto startText = _begin;
    while (currStartBlock != end) {
        auto endBlock = blockParser.set(currStartBlock->prefix().second, _end);
        textParser.set(startText, currStartBlock->prefix().second);
        nodeQueue.push(textParser.parse());
        nodeQueue.push(blockParser.parse());
        startText = endBlock;
        currStartBlock++;
    }
    textParser.set(startText, _end);
    nodeQueue.push(textParser.parse());
}
