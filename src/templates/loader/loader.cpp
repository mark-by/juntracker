#include <loader/loader.h>
#include <parser/re_tags.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <parser/parser.h>

templates::Loader::Loader(const std::string &settingsPath)  {
    boost::filesystem::path path(settingsPath);
    try {
        auto settingsJSON = fileToStr(path);
        templates::Context settings(settingsJSON);
        boost::filesystem::path projectPath = settings.get<std::string>("PROJECT_PATH");
        _templatesPath = projectPath;
        _includesPath = projectPath;
        _templatesPath.append(settings.get<std::string>("TEMPLATES_PATH"));
        _includesPath.append(settings.get<std::string>("INCLUDES_PATH"));
    } catch (const boost::filesystem::filesystem_error& error) {}
}

std::string templates::Loader::fileToStr(const boost::filesystem::path & filePath) {
    int fd = open(filePath.c_str(), O_RDONLY);
    size_t fileSize = boost::filesystem::file_size(filePath);
    std::string result((char *) mmap(nullptr, fileSize, PROT_READ,
                                   MAP_FILE | MAP_SHARED, fd, 0), fileSize);
    close(fd);
    return result;
}

void templates::Loader::load(const std::string &filename) {
    boost::filesystem::path mainPath = _templatesPath.append(filename);
    std::string mainFile = fileToStr(mainPath);
    std::string exFileName = extendFileName(mainFile);
    if (exFileName.empty()) {
        _result = std::move(mainFile);
    } else {
        boost::filesystem::path extendPath = mainPath.branch_path().append(exFileName);
        std::string exFile = fileToStr(extendPath);
        auto blocks = _parser.collectBlocks(mainFile.cbegin(), mainFile.cend());
        auto textBlockQueue = _parser.parseBlocks(exFile.cbegin(), exFile.cend());
        textBlockQueue.renderLoaded(blocks);
        _result = textBlockQueue.result();
    }
    auto [textIncludeQueue, includes] = _parser.parseIncludes(_result.cbegin(), _result.cend());
    if (!includes.empty()) {
        fillIncludes(includes);
        textIncludeQueue.renderLoaded(includes);
        _result = textIncludeQueue.result();
    }

}

void templates::Loader::fillIncludes(std::unordered_map<std::string, std::shared_ptr<templates::Node>> & includes) {
    templates::TextParser textParser;
    for (auto & pair : includes) {
        auto includeStr = fileToStr(_includesPath.append(pair.first));
        textParser.set(includeStr.cbegin(), includeStr.cend());
        pair.second = textParser.parse();
    }
}

std::string templates::Loader::result() const {
    return _result;
}

std::string templates::Loader::extendFileName(const std::string &file_str) {
    std::smatch match;
    std::regex_search(file_str, match, parser::tag::extends);
    return match.format("$2");
}
