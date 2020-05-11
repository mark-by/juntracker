//#include <loader/loader.h>
#include <iostream>
#include <template/template.h>
#include <parser/re_tags.h>

int main() {
    std::string filename = "../../test/templates_test/test_files/loader/loader_extends.html";
    templates::Template templ(filename);
    templates::Context context;
    context.put("b", true);
    context.put("var", 35585);
    context.putArray("array", std::vector<int>{1,2,3,4});
    context.putArray("jarray", std::vector<int>{55, 66, 77});
    templ.render(context);
    std::cout << templ.result() << std::endl;
//
//    std::string filename = "{% include var %} {% for i in range %} {% endfor %}";
//    std::regex tag(BLOCK_TAG_START R"(\s*include\s+([\w.]+)\s*)" BLOCK_TAG_END);
//    std::sregex_iterator smth(filename.cbegin(), filename.cend(), tag);
//    std::cout << smth->format("$1");
//    return 0;
}
