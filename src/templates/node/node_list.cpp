#include <node/node_list.h>
#include <algorithm>

bool templates::NodeList::render() {
    // функция рендерит элемент, который стоит первым в списке и результат кладет в result
    // если элемент можно отрендерить. Функция возвращает false в случае неудачного рендеренга
    // true - в случае удачно. Если удачно, то удаляет отрендеренный массив из списка
    return false;
}

std::string templates::NodeList::getResult() {
    // функция возвращает окончательный результат рендеринга
    return std::string();
}

std::string templates::NodeList::renderAll() {
    while (render());
    return getResult();
}

templates::NodeList::NodeList(templates::Context context, std::vector<Node *> expanded) : context(std::move(context)), result(""){
    std::copy(expanded.begin(), expanded.end(), begin());
}
