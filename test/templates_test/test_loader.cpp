#include "gtest/gtest.h"
#include "loader/loader.h"
#include <string>
#include <fstream>
#include <streambuf>

TEST(LoaderTest, ResultTest) {
    templates::Loader loader;
    loader.load("template.html");
    std::string result = loader.result();
    std::ifstream resultFile("../../../test/templates_test/test_files/templates/loader_result.html");
    std::string shouldResult((std::istreambuf_iterator<char>(resultFile)), std::istreambuf_iterator<char>());
    resultFile.close();
    EXPECT_TRUE(result == shouldResult);
}
