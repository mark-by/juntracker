#ifndef TEMPLATES_NODE_LIST_H
#define TEMPLATES_NODE_LIST_H

#include <node/node.h>
#include <list>
#include <utility>

namespace templates {
    class NodeList : public std::list<Node*> {
    public:
        NodeList() : result("") {};
        explicit NodeList(templates::Context context):context(std::move(context)), result("") {};
        NodeList(templates::Context context, std::vector<Node *> expanded);
        bool render();
        std::string renderAll();

        std::string getResult();

    private:
        templates::Context context;
        std::string result;
    };
}


#endif //TEMPLATES_NODE_LIST_H
