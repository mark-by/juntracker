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
        std::string result() const;

    private:
        void fillIncludes(std::unordered_map<std::string, std::shared_ptr<templates::Node>> & includes);

        static std::string fileToStr(const boost::filesystem::path & filePath) ;

        static std::string extendFileName(const std::string &file_str) ;

        boost::filesystem::path _templatesPath;
        boost::filesystem::path _includesPath;
        std::string _result;
        templates::Parser _parser;
    };
}

#endif //TEMPLATES_LOADER_INCLUDED
