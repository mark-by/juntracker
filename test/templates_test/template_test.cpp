#include "gtest/gtest.h"
#include <template/template.h>
#include <fstream>

TEST (Template, render) {
    templates::Template templ;
    templates::Context context;
    context.put("b", true);
    context.put("var", 35585);
    context.putArray("array", std::vector<int>{1,2,3,4});
    context.putArray("jarray", std::vector<int>{55, 66, 77});

    std::string filename = "template.html";
    templ.set(filename);
    std::ifstream resultFile("../../../test/templates_test/test_files/templates/template_result.html");
    std::string shouldResult((std::istreambuf_iterator<char>(resultFile)), std::istreambuf_iterator<char>());
    resultFile.close();
    EXPECT_EQ(templ.render(context), shouldResult);
}