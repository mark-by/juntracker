#ifndef CORE_API_H
#define CORE_API_H

#include <string>
#include <student.h>
#include <lesson.h>
#include <context/context.h>
#include <teacher.h>
#include <template/template.h>
#include <user.h>
#include <unordered_map>
#include <tuple>


class API {

public:
    virtual std::string getMainPage(const User & user) = 0;
protected:
    static std::tuple<std::string, bool> fetch(const std::string & key, const std::unordered_multimap<std::string, std::string> & data);
    std::string get(const std::string & key, const std::unordered_multimap<std::string, std::string> & data);

    template<class Person>
    struct SimplePersonSerializer {
        templates::Context operator()(const Person &person) {
            templates::Context context;
            context.put("name", person.name() + " " + person.surname());
            context.put("id", person.id());
            return context;
        }
    };

    template<class Title>
    struct SimpleTitleSerializer {
        templates::Context operator()(const Title &title) {
            templates::Context context;
            context.put("title", title.title());
            context.put("id", title.id());
            return context;
        }
    };

    templates::Template _render;
};


#endif //CORE_API_H
