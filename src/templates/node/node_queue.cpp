#include <node/node.h>
#include <algorithm>

bool templates::NodeQueue::render() {
    // функция рендерит элемент, который стоит первым в списке и результат кладет в result
    // если элемент можно отрендерить. Функция возвращает false в случае неудачного рендеренга
    // true - в случае удачно. Если удачно, то удаляет отрендеренный массив из списка
    return false;
}

std::string templates::NodeQueue::getResult() {
    // функция возвращает окончательный результат рендеринга
    return std::string();
}

std::string templates::NodeQueue::renderAll() {
    while (render());
    return getResult();
}

