#include <loader/loader.h>
#include <fstream>
#include <parser/re_tags.h>
#include <sys/mman.h>
#include <boost/filesystem.hpp>
#include <fcntl.h>
#include <iostream>
#include <parser/parser.h>

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

    std::string extendFileName = BlockParser::getName(match.str());
    boost::filesystem::path extendPath = filePath.branch_path().append(extendFileName);
    close(fd);
    fd = open(extendPath.c_str(), O_RDONLY);
    size_t extendFileSize = boost::filesystem::file_size(extendPath);
    std::string extendFile((char *) mmap(nullptr, extendFileSize, PROT_READ,
                                   MAP_FILE | MAP_SHARED, fd, 0), extendFileSize);

    auto blocks = parser.collectBlocks(match.suffix().first, match.suffix().second);
    auto nodeQueue = parser.parseBlocks(extendFile.cbegin(), extendFile.cend());
    nodeQueue.renderLoaded(blocks);
    _result = nodeQueue.result();
}

std::string templates::Loader::result() {
    return _result;
}

