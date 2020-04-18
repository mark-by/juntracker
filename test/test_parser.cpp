#include "gtest/gtest.h"
#include "parser/parser.h"
#include "node/node.h"

TEST(Parser, textParser) {
    std::string someText = "some text";
    templates::TextParser textParser;
    textParser.init(someText);
    std::unique_ptr<templates::Node> resultNode = textParser.parse();
    EXPECT_EQ(resultNode->get_type(), TEXTNODE);
    templates::Context context;
    EXPECT_EQ(resultNode->render(context), someText);
}
