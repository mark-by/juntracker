#ifndef CONTEXT_IMPL_INCLUDED
#define CONTEXT_IMPL_INCLUDED

std::string templates::Context::str() const {
    // Представление context в json в строковом виде
    std::ostringstream oss;
    boost::property_tree::write_json(oss, root);
    return oss.str();
}

template<class T>
void templates::Context::put(const char *name, T value) {
    // Метод добавляет переменную c именем name и значение value  в context
    // В случе, если name содержит '.', напрмер "person.name", то создается обхект person с полем name
    // Последующие указание с тем же именем объекта (например "person.age") добавит к объекту поле age
    root.put(name, value);
}

template<class T>
T templates::Context::get(const char *name) {
    // Метод позволяет взять переменную по ключу
    return root.get<T>(name);
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
void templates::Context::putArray(const char *name, const T *array, size_t count, Serializer serial) {
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
void templates::Context::putArray(const char *name, const std::vector<T> &array, Serializer serial) {
    // Метод позволяет создать массив в контексте. Для простых данных собственный serializer не нужен
    // Для пользовательских данных, объектов, необходимо создать функцию Serializer, которая возвращает объект
    // Context - представление объекта в контексте
    boost::property_tree::ptree ptArray;
    for (auto &item : array) {
        ptArray.push_back(std::make_pair("", serial(item).root));
    }
    root.add_child(name, ptArray);
}

std::vector<templates::Context> templates::Context::getObjects(boost::property_tree::ptree::key_type const &key) {
    std::vector<Context> temp;
    for (auto& item : root.get_child(key))
        temp.push_back(Context(item.second));
    return temp;
}

#endif
