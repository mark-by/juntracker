#include "gtest/gtest.h"
#include "parser/parser.h"
#include "node/node.h"
#include <parser/re_tags.h>

TEST(NodeParser, TextParser) {
    std::string someText = "some text";
    templates::TextParser textParser;
    textParser.set(someText.cbegin(), someText.cend());
    std::shared_ptr<templates::Node> resultNode = textParser.parse();
    EXPECT_EQ(resultNode->type(), templates::TEXTNODE);
    EXPECT_EQ(resultNode->content(), someText);
}

TEST(NodeParser, VarParser) {
    std::string content = "{{ number  }}df";
    templates::VarParser varParser;
    std::sregex_iterator tag(content.cbegin(), content.cend(), parser::tag::any);
    auto end = varParser.set(tag);
    EXPECT_EQ(*end, 'd');
    std::shared_ptr<templates::Node> resultNode = varParser.parse();
    EXPECT_EQ(templates::VARNODE, resultNode->type());
    templates::Context context;
    context.put("number", 1);
    EXPECT_EQ(resultNode->render(context), " 1  ");
}

TEST(NodeParser, ForParser) {
    std::string content = "{% for number in array %}number: {{number}} {% for j in array2 %}do{%endfor%}{% endfor %}end";
    templates::ForParser forParser;
    std::sregex_iterator tag(content.cbegin(), content.cend(), parser::tag::any);
    auto end = forParser.set(tag);
    std::shared_ptr<templates::Node> resultNode = forParser.parse();
    EXPECT_EQ(templates::FORNODE, resultNode->type());
    EXPECT_EQ(resultNode->name(), "number");
    EXPECT_EQ(resultNode->content(), "number: {{number}} {% for j in array2 %}do{%endfor%}");
    EXPECT_EQ(*end, 'e');
}

TEST(NodeParser, BlockParser) {
    std::string content = "{% block number %}number: {{number}}{% endblock %}end";
    templates::BlockParser blockParser;
    std::sregex_iterator tag(content.cbegin(), content.cend(), parser::tag::any);
    auto end = blockParser.set(tag);
    std::shared_ptr<templates::Node> resultNode = blockParser.parse();
    EXPECT_EQ(templates::BLOCKNODE, resultNode->type());
    EXPECT_EQ(resultNode->name(), "number");
    EXPECT_EQ(resultNode->content(), "number: {{number}}");
    EXPECT_EQ(*end, 'e');
}

TEST(NodeParser, IfParserOneElse) {
    std::string content = "{% if isTrue %}{% if anotherTrue %}do anotherTrue {% endif %}{% else %}{% if anotherInFalse %}do another in false{%endif%}{%endif%}end";
    templates::IfParser ifParser;
    std::sregex_iterator tag(content.cbegin(), content.cend(), parser::tag::any);
    auto end = ifParser.set(tag);
    std::shared_ptr<templates::Node> resultNode = ifParser.parse();
    EXPECT_EQ(templates::IFNODE, resultNode->type());
    EXPECT_EQ(resultNode->name(), "{% if anotherTrue %}do anotherTrue {% endif %}");
    EXPECT_EQ(resultNode->content(), "{% if anotherInFalse %}do another in false{%endif%}");
    EXPECT_EQ(*end, 'e');
}


TEST(NodeParser, IfParserTwoElse) {
    std::string content = "{% if isTrue %}{% if anotherTrue %}do anotherTrue {%else%} do smth else {% endif %}{% else %}{% if anotherInFalse %}do another in false{%endif%}{%endif%}end";
    templates::IfParser ifParser;
    std::sregex_iterator tag(content.cbegin(), content.cend(), parser::tag::any);
    auto end = ifParser.set(tag);
    std::shared_ptr<templates::Node> resultNode = ifParser.parse();
    EXPECT_EQ(templates::IFNODE, resultNode->type());
    EXPECT_EQ(resultNode->name(), "{% if anotherTrue %}do anotherTrue {%else%} do smth else {% endif %}");
    EXPECT_EQ(resultNode->content(), "{% if anotherInFalse %}do another in false{%endif%}");
    EXPECT_EQ(*end, 'e');
}

TEST(NodeParser, IfThreeTwoElse) {
    std::string content = "{% if isTrue %}{% if anotherTrue %}do anotherTrue {%else%} do smth else {% endif %}{% else %}{% if anotherInFalse %}do anotherTrue {%else%} do smth else {%endif%}{%endif%}end";
    templates::IfParser ifParser;
    std::sregex_iterator tag(content.cbegin(), content.cend(), parser::tag::any);
    auto end = ifParser.set(tag);
    std::shared_ptr<templates::Node> resultNode = ifParser.parse();
    EXPECT_EQ(templates::IFNODE, resultNode->type());
    EXPECT_EQ(resultNode->name(), "{% if anotherTrue %}do anotherTrue {%else%} do smth else {% endif %}");
    EXPECT_EQ(resultNode->content(), "{% if anotherInFalse %}do anotherTrue {%else%} do smth else {%endif%}");
    EXPECT_EQ(*end, 'e');
}
