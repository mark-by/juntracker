#include "gtest/gtest.h"
#include "node/node.h"
#include <context/context.h>

TEST(Node, TestTextNode) {
    templates::TextNode textNode("", "  \n  some text {{ text }}   \n \n \n  ");
    EXPECT_EQ(textNode.type(), templates::TEXTNODE);
    templates::Context context;
    EXPECT_EQ(textNode.render(context), "some text {{ text }}");
}

TEST(Node, TestBlockNode) {
    templates::BlockNode blockNode("menu", " \n   some content \n  \t");
    EXPECT_EQ(blockNode.type(), templates::BLOCKNODE);
    EXPECT_EQ(blockNode.name(), "menu");
    templates::Context context;
    EXPECT_EQ(blockNode.render(context), "some content");
}

TEST(Node, TestVarNode) {
    templates::Context context;
    context.put("number", 72);
    templates::VarNode varNode("number", "  ", "");
    EXPECT_EQ("  72", varNode.render(context));
}

TEST(Node, TestForNode) {
    templates::Context context;
    std::vector<int> numbers = {1, 2, 3, 4};
    context.putArray("array", numbers);
    templates::ForNode forNode("i", "Number: {{ i }}", "array");
    EXPECT_EQ(forNode.render(context), "Number: 1 Number: 2 Number: 3 Number: 4 ");
}

TEST(Node, TestIfNode) {
    templates::Context trueContext;
    trueContext.put("statement", true);
    templates::Context falseContext;
    falseContext.put("statement", false);
    templates::IfNode ifNode("This should render if statement is true", "This should render if statement is false", "statement");
    EXPECT_EQ(ifNode.render(trueContext), "This should render if statement is true");
    EXPECT_EQ(ifNode.render(falseContext), "This should render if statement is false");
}
