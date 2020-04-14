#ifndef CONTEXT_INCLUDED
#define CONTEXT_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <string>

namespace templates {
    template <class T>
    struct DefaultSerializer;


    class Context {
    public:
        Context() = default;
        explicit Context(boost::property_tree::ptree &root) : root(root) {};

        explicit Context(std::string json);

        template <class T, class Serializer = DefaultSerializer<T>>
        inline void putArray(const char * name, const T * array, size_t count, Serializer serial = Serializer());

        template <class T, class Serializer = DefaultSerializer<T>>
        inline void putArray(const char * name, const std::vector<T> & array, Serializer serial = Serializer());

        inline std::string str() const;

        template<class T>
        inline void put(const char *name, T value);

        template<class T>
        inline T get(const char *name);

        template<class T>
        inline std::vector <T> getArray(boost::property_tree::ptree::key_type const &key);

        inline std::vector<Context> getObjects(boost::property_tree::ptree::key_type const &key);

    private:
        boost::property_tree::ptree root;
    };

    template <class T>
    struct DefaultSerializer {
        Context operator() (const T& obj){
            Context temp;
            temp.put("", obj);
            return temp;
        }
    };
}

#include "../../src/templates/context/context_impl.h"
#endif //CONTEXT_INCLUDED
