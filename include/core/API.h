#ifndef CORE_API_H
#define CORE_API_H

#include <string>
#include <student.h>
#include <lesson.h>
#include <context/context.h>
#include <teacher.h>

class API {
public:
    virtual std::string getMainPage(int user_id) = 0;

protected:
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
};


#endif //CORE_API_H
