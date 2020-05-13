#include <iostream>
#include <template/template.h>

int main() {
    std::string settings_path = "../../test/templates_test/test_files/settings";
    templates::Template templ(settings_path);
    templates::Context context;
    context.put("b", true);
    context.put("var", 35585);
    context.putArray("array", std::vector<int>{1,2,3,4});
    context.putArray("jarray", std::vector<int>{55, 66, 77});

    std::string filename = "template.html";
    templ.set(filename);
    std::cout << templ.render(context) << std::endl;
    return 0;
}
