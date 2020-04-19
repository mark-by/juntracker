#include "gtest/gtest.h"
#include "node/node.h"

TEST(Node, TestTextNode) {
    templates::TextNode textNode("", "some text");
    EXPECT_EQ(textNode.getType(), TEXTNODE);
    EXPECT_EQ(textNode.render(templates::Context()), "some text");
    EXPECT_TRUE(textNode.expand().empty());
}

TEST(Node, TestBlockNode) {
    templates::BlockNode blockNode("menu", "some content");
    EXPECT_EQ(blockNode.getType(), BLOCKNODE);
    EXPECT_EQ(blockNode.render(templates::Context()), "some content");
    EXPECT_TRUE(blockNode.expand().empty());
}

TEST(Node, TestVarNode) {
    templates::Context context;
    context.put("number", 72);
    templates::VarNode varNode("number", "{{ number }}");
    EXPECT_EQ("72", varNode.render(context));
    EXPECT_TRUE(varNode.expand().empty());
}

TEST(Node, TestForNode) {
    templates::Context context;
    std::vector<int> numbers = {1, 2, 3, 4};
    context.putArray("array", numbers);
    templates::ForNode forNode("number:array", "Number: {{ number }}");
    EXPECT_EQ(forNode.render(context), "Number: 1Number: 2Number: 3Number: 4");
    templates::NodeQueue expandedFor = forNode.expand();
    ASSERT_EQ(expandedFor.size(), 2);
    EXPECT_EQ(expandedFor.front()->getType(), TEXTNODE);
    expandedFor.pop();
    EXPECT_EQ(expandedFor.front()->getType(), VARNODE);
}

TEST(Node, TestIfNode) {
    templates::Context context;
    context.put("isLogged", true);
    templates::Context falseContext;
    context.put("isLogged", false);
    templates::IfNode ifNode("isLogged", "Hello!{% endif %}");
    ifNode.setElseContent("You should be logged in");
    EXPECT_EQ(ifNode.render(context), "Hello!");
    EXPECT_EQ(ifNode.render(falseContext), "You should be logged in");
}
