#ifndef TEMPLATES_LOADER_INCLUDED
#define TEMPLATES_LOADER_INCLUDED

#include <node/node.h>
#include <parser/parser.h>
#include <unordered_map>
#include <boost/filesystem.hpp>

namespace templates {
    class Loader {
    public:
        explicit Loader(const std::string &settingsPath = "settings");

        void load(const std::string &filename);
        std::string result();

    private:
        void fillIncludes(std::unordered_map<std::string, std::shared_ptr<templates::Node>> & includes);

        std::string fileToStr(const boost::filesystem::path & filePath);

        std::string extendFileName(const std::string &file_str);

        boost::filesystem::path templatesPath;
        boost::filesystem::path includesPath;
        std::string _result;
        templates::Parser parser;
    };
}

#endif //TEMPLATES_LOADER_INCLUDED
