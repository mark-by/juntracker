#include "gtest/gtest.h"
#include <parser/parser.h>

templates::Parser parser;
std::string textBlocks = "some text{% block b1 %}someBlock{%endblock%}some text{%block b2%}someBlock2{%endblock%}some text";

TEST(Parser, collectBlocks) {
    auto blockTable = parser.collectBlocks(textBlocks.cbegin(), textBlocks.cend());
    EXPECT_EQ(blockTable.size(), 2);
    EXPECT_EQ(blockTable["b1"]->content(), "someBlock");
    EXPECT_EQ(blockTable["b2"]->content(), "someBlock2");
}

TEST(Parser, parseBlocks) {
    auto nodeQueueWithBlockAndText = parser.parseBlocks(textBlocks.cbegin(), textBlocks.cend());
    std::array<std::pair<std::string, std::string>, 2> blocks;
    blocks[0] = std::make_pair("b1", "someBlock");
    blocks[1] = std::make_pair("b2", "someBlock2");
    EXPECT_EQ(nodeQueueWithBlockAndText.size(), 5);
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(nodeQueueWithBlockAndText.front()->type(), templates::TEXTNODE);
        EXPECT_EQ(nodeQueueWithBlockAndText.front()->content(), "some text");
        nodeQueueWithBlockAndText.pop();
        EXPECT_EQ(nodeQueueWithBlockAndText.front()->type(), templates::BLOCKNODE);
        EXPECT_EQ(nodeQueueWithBlockAndText.front()->name(), blocks[i].first);
        EXPECT_EQ(nodeQueueWithBlockAndText.front()->content(), blocks[i].second);
        nodeQueueWithBlockAndText.pop();
    }
}

TEST(Parser, parseIncludes) {
    std::string textIncludes = "some text{% include base.html %}some text{% include some.html %}some text";
    auto [nodeQueueWithIncAndText, incTable] = parser.parseIncludes(textIncludes.cbegin(), textIncludes.cend());
    EXPECT_EQ(incTable.size(), 2);
    std::array<std::string, 2> includes;
    includes[0] = "base.html";
    includes[1] = "some.html";
    EXPECT_EQ(nodeQueueWithIncAndText.size(), 5);
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(nodeQueueWithIncAndText.front()->type(), templates::TEXTNODE);
        EXPECT_EQ(nodeQueueWithIncAndText.front()->content(), "some text");
        nodeQueueWithIncAndText.pop();
        EXPECT_EQ(nodeQueueWithIncAndText.front()->type(), templates::INCLUDENODE);
        EXPECT_EQ(nodeQueueWithIncAndText.front()->name(), includes[i]);
        nodeQueueWithIncAndText.pop();
    }
}

TEST(Parser, parse) {
    std::string text = "some text{{ var }}{% for i in range %}{%endfor%}{%if b%}{%else%}{%endif%}some text";
    auto nodeQueue = parser.parse(text.cbegin(), text.cend());
    EXPECT_EQ(nodeQueue.size(), 5);
    std::array<int, 5> types = {templates::TEXTNODE, templates::VARNODE,templates::FORNODE, templates::IFNODE, templates::TEXTNODE};
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(nodeQueue.front()->type(), types[i]);
        nodeQueue.pop();
    }
}
