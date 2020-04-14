#include "gtest/gtest.h"
#include "node/node.h"

TEST(Node, TestTextNode) {
    templates::TextNode textNode("", "some text");
    EXPECT_EQ(textNode.get_type(), TEXTNODE);
    EXPECT_EQ(textNode.render(templates::Context()), "some text");
    EXPECT_TRUE(textNode.expand().empty());
}

TEST(Node, TestBlockNode) {
    templates::BlockNode blockNode("menu", "some content");
    EXPECT_EQ(blockNode.get_type(), BLOCKNODE);
    EXPECT_EQ(blockNode.render(templates::Context()), "some text");
    EXPECT_TRUE(blockNode.expand().empty());
}
