//#include <loader/loader.h>
#include <iostream>
#include <template/template.h>

int main() {
    std::string filename = "../../test/templates_test/test_files/loader/loader_extends.html";
    templates::Template templ(filename);
    templates::Context context;
    context.put("b", true);
    context.put("var", 35585);
    context.putArray("array", std::vector<int>{4,5,3,2});
    context.putArray("jarray", std::vector<int>{55, 45, 66});
    templ.render(context);
    std::cout << templ.result() << std::endl;
    return 0;
}
