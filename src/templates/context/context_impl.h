#ifndef CONTEXT_IMPL_INCLUDED
#define CONTEXT_IMPL_INCLUDED
#include <context/context.h>

inline std::string templates::Context::str() const {
    // Представление context в json в строковом виде
    std::ostringstream oss;
    boost::property_tree::write_json(oss, root);
    return oss.str();
}

inline templates::Context::Context(const std::string &json) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::read_json(ss, root);
}

template<class T>
void templates::Context::put(std::string name, T value) {
    // Метод добавляет переменную c именем name и значение value  в context
    // В случе, если name содержит '.', напрмер "person.name", то создается обхект person с полем name
    // Последующие указание с тем же именем объекта (например "person.age") добавит к объекту поле age
    root.put(std::move(name), std::move(value));
}

template<class T>
T templates::Context::get(std::string name) {
    // Метод позволяет взять переменную по ключу
    return root.get<T>(std::move(name));
}

template<class T>
std::vector<T> templates::Context::getArray(boost::property_tree::ptree::key_type const &key) {
    // Метод позволяет получить массив в качестве вектора
    std::vector<T> temp;
    for (auto& item : root.get_child(key))
        temp.push_back(item.second.get_value<T>());
    return temp;
}

template<class T, class Serializer>
void templates::Context::putArray(std::string name, const T *array, size_t count, Serializer serial) {
    // Метод позволяет создать массив в контексте. Для простых данных собственный serializer не нужен
    // Для пользовательских данных, объектов, необходимо создать функцию Serializer, которая возвращает объект
    // Context - представление объекта в контексте
    boost::property_tree::ptree ptArray;
    for (size_t i=0; i< count; i++) {
        ptArray.push_back(std::make_pair("", serial(array[i]).root));
    }
    root.add_child(std::move(name), ptArray);
}

template<class T, class Serializer>
void templates::Context::putArray(std::string name, const std::vector<T> &array, Serializer serial) {
    // Метод позволяет создать массив в контексте. Для простых данных собственный serializer не нужен
    // Для пользовательских данных, объектов, необходимо создать функцию Serializer, которая возвращает объект
    // Context - представление объекта в контексте
    boost::property_tree::ptree ptArray;
    for (auto &item : array) {
        ptArray.push_back(std::make_pair("", serial(item).root));
    }
    root.add_child(std::move(name), ptArray);
}

inline std::vector<templates::Context> templates::Context::getObjects(boost::property_tree::ptree::key_type const &key) {
    std::vector<Context> temp;
    for (auto& item : root.get_child(key))
        temp.push_back(Context(item.second));
    return temp;
}

#endif
