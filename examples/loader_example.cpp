//#include <loader/loader.h>
#include <iostream>
#include <template/template.h>

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
    return 0;
}
