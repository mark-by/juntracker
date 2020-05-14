#include "gtest/gtest.h"
#include <boost/filesystem.hpp>
#include <context/context.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto testProjPath = boost::filesystem::current_path().parent_path().parent_path().parent_path().append(
            "/test/templates_test/test_files/");
    boost::filesystem::path includes = "inc/";
    boost::filesystem::path templates = "templates/";
    templates::Context settings;
    settings.put("PROJECT_PATH", testProjPath.c_str());
    settings.put("INCLUDES_PATH", includes.c_str());
    settings.put("TEMPLATES_PATH", templates.c_str());
    std::ofstream testSettingsFile("settings");
    testSettingsFile << settings.str();
    testSettingsFile.close();
    return RUN_ALL_TESTS();
}
