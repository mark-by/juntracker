#include "gtest/gtest.h"
#include "parser/parser.h"
#include "node/node.h"

TEST(Parser, TextParser) {
    std::string someText = "some text";
    templates::TextParser textParser;
    textParser.init(someText);
    std::unique_ptr<templates::Node> resultNode = textParser.parse();
    EXPECT_EQ(resultNode->getType(), templates::TEXTNODE);
    EXPECT_EQ(resultNode->getContent(), someText);
}

TEST(Parser, VarParser) {
    std::string content = "{{ number }}";
    templates::VarParser varParser;
    varParser.init(content);
    std::unique_ptr<templates::Node> resultNode = varParser.parse();
    EXPECT_EQ(templates::VARNODE, resultNode->getType());
    EXPECT_EQ(resultNode->getContent(), "number");
}

TEST(Parser, ForParser) {
    std::string content = "{% for number in array %}number: {{number}}{% endfor %}";
    templates::ForParser forParser;
    forParser.init(content);
    std::unique_ptr<templates::Node> resultNode = forParser.parse();
    EXPECT_EQ(templates::FORNODE, resultNode->getType());
    EXPECT_EQ(resultNode->getName(), "number:array");
    EXPECT_EQ(resultNode->getContent(), "number: {{number}}");
}

TEST(Parser, BlockParser) {
    std::string content = "{% block number %}number: {{number}}{% endblock %}";
    templates::BlockParser blockParser;
    blockParser.init(content);
    std::unique_ptr<templates::Node> resultNode = blockParser.parse();
    EXPECT_EQ(templates::BLOCKNODE, resultNode->getType());
    EXPECT_EQ(resultNode->getName(), "numbej");
    EXPECT_EQ(resultNode->getContent(), "number: {{number}}");
}


TEST(Parser, IfParser) {
    std::string content = "{% block number %}number: {{number}}{% endblock %}";
    templates::BlockParser blockParser;
    blockParser.init(content);
    std::unique_ptr<templates::Node> resultNode = blockParser.parse();
    EXPECT_EQ(templates::BLOCKNODE, resultNode->getType());
    EXPECT_EQ(resultNode->getName(), "number");
    EXPECT_EQ(resultNode->getContent(), "number: {{number}}");
}
