#include <template/template.h>
#include <iostream>

int main(int args, char ** argv) {
    if (args != 5) {
        std::cout << args << std::endl;
        std::cout << "Usage: <file_to_render> <contextJson> <settings_file> <outputfile>" << std::endl;
        return 0;
    }
    std::string templateName(argv[1]);
    std::string contextFileName(argv[2]);
    std::string settingsFileName(argv[3]);
    std::string outputFileName(argv[4]);
    templates::Template templ(settingsFileName);
    std::ifstream contextFile(contextFileName);
    std::string json;
    char symbol;
    while (contextFile.get(symbol)) {
        json.push_back(symbol);
    }
    contextFile.close();
    templates::Context context(json);
    templ.set(templateName);
    std::string result = templ.render(context);
    std::ofstream output(outputFileName);
    for (auto & _symbol : result) {
        output << _symbol;
    }
    output.close();
}