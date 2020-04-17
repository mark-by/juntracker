#include "gtest/gtest.h"
#include "loader/loader.h"
#include <string>
#include <fstream>
#include <streambuf>

TEST(LoaderTest, SomeTest) {
    templates::Loader loader("../../test/test_files/loader/loader_extends.html");
    loader.load();
    std::string result = loader.getResult();
    std::ifstream resultFile("../../test/test_files/loader/loader_result.html");
    std::string shouldResult((std::istreambuf_iterator<char>(resultFile)), std::istreambuf_iterator<char>());
    EXPECT_TRUE(result == shouldResult);
}
