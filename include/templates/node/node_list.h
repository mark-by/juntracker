#ifndef TEMPLATES_NODE_LIST_H
#define TEMPLATES_NODE_LIST_H

#include <node/node.h>
#include <list>

namespace templates {
    class NodeList : public std::list<Node*> {
    public:
        NodeList() : result("") {};

        bool render();

        std::string getResult();

    private:
        void insertNodes(std::list<Node*>::iterator it, std::vector<Node*> nodes);

        templates::Context context;
        std::string result;
    };
}


#endif //TEMPLATES_NODE_LIST_H
