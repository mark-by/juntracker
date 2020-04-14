#include <node/node_list.h>

bool templates::NodeList::render() {
    return false;
}

std::string templates::NodeList::getResult() {
    return std::string();
}

void templates::NodeList::insertNodes(std::list<Node*>::iterator it, std::vector<Node*> nodes) {

}
