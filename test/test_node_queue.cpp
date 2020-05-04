#include "gtest/gtest.h"
#include <node/node.h>

TEST(NodeList, renderList) {
    templates::Context context;
    context.put("name", "Mark");
    context.putArray("array", std::vector<int>({1,2,3}));
    templates::NodeQueue nodeList(context);
    nodeList.push(std::make_unique<templates::TextNode>("", "some text"));
    nodeList.push(std::make_unique<templates::TextNode>("", " some text2"));
    nodeList.push(std::make_unique<templates::VarNode>("name", "{{ name }}"));
    nodeList.push(std::make_unique<templates::ForNode>("number:array", "Number: {{ number }}"));
    EXPECT_TRUE(nodeList.render());
    EXPECT_EQ(nodeList.getResult(), "some text");
    EXPECT_TRUE(nodeList.render());
    EXPECT_EQ(nodeList.getResult(), "some text some text2");
    EXPECT_TRUE(nodeList.render());
    EXPECT_EQ(nodeList.getResult(), "some text some text2Mark");
    EXPECT_TRUE(nodeList.render());
    EXPECT_EQ(nodeList.getResult(), "some text some text2MarkNumber: 1Number: 2Number: 3");
    EXPECT_FALSE(nodeList.render());
    EXPECT_EQ(nodeList.getResult(), "some text some text2MarkNumber: 1Number: 2Number: 3");
}

TEST(NodeList, renderAllList) {
    templates::Context context;
    context.put("name", "Mark");
    context.putArray("array", std::vector<int>({1,2,3}));
    templates::NodeQueue nodeList(context);
    nodeList.push(std::make_unique<templates::TextNode>("", "some text"));
    nodeList.push(std::make_unique<templates::TextNode>("", " some text2"));
    nodeList.push(std::make_unique<templates::VarNode>("name", "{{ name }}"));
    nodeList.push(std::make_unique<templates::ForNode>("number:array", "Number: {{ number }}"));
    EXPECT_EQ(nodeList.renderAll(), "some text some text2MarkNumber: 1Number: 2Number: 3");
}


