#include "gtest/gtest.h"
#include <context/context.h>
#include <string>

TEST(Context, putGetContext) {
    templates::Context context;
    context.put("name", "Vladimir");
    context.put("age", 15);
    EXPECT_EQ("Vladimir", context.get<std::string>("name"));
    EXPECT_EQ(context.get<int>("age"), 15);
}

TEST(Context, putSimpleArray) {
    templates::Context context;
    std::vector<int> testArray = {32,4,3,24,5,43};
    context.putArray("array", testArray);
    std::vector<int> resultArray = context.getArray<int>("array");
    for (int i =0; i < 6; i++) {
        EXPECT_EQ(testArray[i], resultArray[i]);
    }
}

TEST(Context, putObjectsArray) {
    struct Person {
        std::string name;
        int age;
        Person(std::string name, int age) : name(name), age(age) {};
        static templates::Context serializePerson(const Person &person) {
            templates::Context context;
            context.put("name", person.name);
            context.put("age", person.age);
            return context;
        }
    };

    templates::Context context;
    std::vector<Person> persons;
    persons.push_back(Person("Homer", 33));
    persons.push_back(Person("John", 25));
    persons.push_back(Person("Katy", 28));
    context.putArray("person", persons, Person::serializePerson);
    std::vector<templates::Context> objects = context.getObjects("person");
    for (int i=0; i < 3; i++) {
        EXPECT_EQ(persons[i].name, objects[i].get<std::string>("name"));
        EXPECT_EQ(persons[i].age, objects[i].get<int>("age"));
    }
}

TEST(Context, createByJson) {
    std::string json = "{ \"name\" : \"Mark\", \"age\" : \"22\" }";
    templates::Context context(json);
    EXPECT_EQ("Mark", context.get<std::string>("name"));
    EXPECT_EQ(22, context.get<int>("age"));
}
