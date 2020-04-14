#include "gtest/gtest.h"
#include <context/context.h>
#include <string>

TEST(Context, someTest) {
    templates::Context context;
    context.put("name", "Vladimir");
    EXPECT_EQ("Vladimir", context.get<std::string>("name"));
}
