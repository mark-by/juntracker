#include "gtest/gtest.h"
#include <node/node_queue.h>
#include <unordered_map>
#include <memory>

TEST(NodeQueue, renderQueue) {
    templates::Context context;
    context.put("name", "Mark");
    context.putArray("array", std::vector<int>({1, 2, 3}));
    templates::NodeQueue nodeQueue;
    nodeQueue.push(std::make_shared<templates::TextNode>("", "<div>some text</div>"));
    nodeQueue.push(std::make_shared<templates::TextNode>("", "<p>some text2</p>"));
    nodeQueue.push(std::make_shared<templates::VarNode>("name", " ", " "));
    nodeQueue.push(std::make_shared<templates::ForNode>("number", "<span>Number: {{ number}}</span>", "array"));
    nodeQueue.render(context);
    EXPECT_EQ(
            "<div>some text</div><p>some text2</p> Mark <span>Number: 1</span><span>Number: 2</span><span>Number: 3</span>",
            nodeQueue.result());
}

TEST(NodeQueue, renderBlocks) {
    std::unordered_map<std::string, std::shared_ptr<templates::Node>> blocks;
    blocks["block1"] = std::make_shared<templates::BlockNode>("block1", "some content");
    blocks["block2"] = std::make_shared<templates::BlockNode>("block2", "some content2");
    blocks["block3"] = std::make_shared<templates::BlockNode>("block3", "some content3");
    templates::NodeQueue nodeQueue;
    nodeQueue.push(std::make_shared<templates::BlockNode>("block1", ""));
    nodeQueue.push(std::make_shared<templates::BlockNode>("block2", ""));
    nodeQueue.push(std::make_shared<templates::BlockNode>("block3", ""));
    nodeQueue.push(std::make_shared<templates::BlockNode>("block4", "some content4"));
    nodeQueue.renderLoaded(blocks);
    EXPECT_EQ("some contentsome content2some content3some content4", nodeQueue.result());
}
