#ifndef CONTEXT_IMPL_INCLUDED
#define CONTEXT_IMPL_INCLUDED
#include <context/context.h>
#include <iostream>

inline std::string templates::Context::str() const {
    // Представление context в json в строковом виде
    std::ostringstream oss;
    try {
        boost::property_tree::write_json(oss, root);
    } catch (...) {
        oss << root.get<std::string>("");
    }
    return oss.str();
}

inline templates::Context::Context(const std::string &json) {
    std::stringstream ss;
    ss << json << '\0';
    std::cout << ss.str() << std::endl;
    boost::property_tree::read_json(ss, root);
}

template<class T>
void templates::Context::put(const std::string &name, const T &value) {
    // Метод добавляет переменную c именем name и значение value  в context
    // В случе, если name содержит '.', напрмер "person.name", то создается обхект person с полем name
    // Последующие указание с тем же именем объекта (например "person.age") добавит к объекту поле age
    root.put(name, value);
}

template<class T>
T templates::Context::get(const std::string &name) const {
    // Метод позволяет взять переменную по ключу
    return root.get<T>(name);
}

template<class T>
std::vector<T> templates::Context::getArray(boost::property_tree::ptree::key_type const &key) const {
    // Метод позволяет получить массив в качестве вектора
    std::vector<T> temp;
    for (auto& item : root.get_child(key))
        temp.push_back(item.second.get_value<T>());
    return temp;
}

template<class T, class Serializer>
void templates::Context::putArray(const std::string& name, const T *array, size_t count, Serializer serial) {
    // Метод позволяет создать массив в контексте. Для простых данных собственный serializer не нужен
    // Для пользовательских данных, объектов, необходимо создать функцию Serializer, которая возвращает объект
    // Context - представление объекта в контексте
    boost::property_tree::ptree ptArray;
    for (size_t i=0; i< count; i++) {
        ptArray.push_back(std::make_pair("", serial(array[i]).root));
    }
    root.add_child(name, ptArray);
}

template<class T, class Serializer>
void templates::Context::putArray(const std::string &name, const std::vector<T> &array, Serializer serial) {
    // Метод позволяет создать массив в контексте. Для простых данных собственный serializer не нужен
    // Для пользовательских данных, объектов, необходимо создать функцию Serializer, которая возвращает объект
    // Context - представление объекта в контексте
    boost::property_tree::ptree ptArray;
    for (auto &item : array) {
        ptArray.push_back(std::make_pair("", serial(item).root));
    }
    root.add_child(name, ptArray);
}

inline std::vector<templates::Context> templates::Context::getObjects(boost::property_tree::ptree::key_type const &key) {
    std::vector<Context> temp;
    for (auto& item : root.get_child(key))
        temp.push_back(Context(item.second));
    return temp;
}

inline void templates::Context::set(const std::string &name, const templates::Context &_root) {
    root.erase(name);
    root.add_child(name, _root.root.get_child(""));
}

inline std::unordered_map<std::string, std::string> templates::Context::toMap() {
    std::unordered_map<std::string, std::string> map;
    auto end = root.end();
    for (auto it = root.begin(); it != end; it++) {
        map[it->first] = it->second.get_value<std::string>();
    }
    return map;
}

#endif
