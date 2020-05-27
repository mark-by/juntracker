#include <context/context.h>
#include <iostream>
#include <string>

struct Person {
    std::string name;
    std::string second_name;
    int age;

    Person() : name(""), second_name(""), age(0) {};
};

templates::Context PersonSerializer(const Person &person) {
    templates::Context context;
    context.put("name", person.name);
    context.put("second_name", person.second_name);
    context.put("age", person.age);
    return context;
}

int main() {

    templates::Context context;

    context.put("name", "Mark Bykhovets");
    context.put("obj.value1", 1);
    context.put("obj.value2", 2);

    int nums[] = {1, 5, 3, 4, 6};
    context.putArray("array", nums, 5);

    std::vector<int> array = {65, 4, 3, 45, 6, 65};
    context.putArray("vector_array", array);

    auto persons = new Person[3];
    persons[0].name = "Josh";
    persons[0].second_name = "Brown";
    persons[0].age = 20;
    persons[1].name = "Homer";
    persons[1].second_name = "Simpson";
    persons[1].age = 31;
    persons[2].name = "Ragnar";
    persons[2].second_name = "Lodbrok";
    persons[2].age = 25;
    context.putArray("person", persons, 3, PersonSerializer);

    std::cout << context.str();

    std::cout << "OUT" << std::endl;

    std::cout << context.get<int>("obj.value2") << std::endl;

    auto numbers = context.getObjects("array");
    for (auto &i : numbers)
        std::cout << i.get<std::string>("") << " ";
    std::cout << std::endl;

    std::vector<templates::Context> persons_context = context.getObjects("person");
    for (auto & i : persons_context) std::cout << i.str();
    return 0;
}

