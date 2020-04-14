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

        template <class T, class Serializer = DefaultSerializer<T>>
        void putArray(const char * name, const T * array, size_t count, Serializer serial = Serializer());

        template <class T, class Serializer = DefaultSerializer<T>>
        void putArray(const char * name, const std::vector<T> & array, Serializer serial = Serializer());

        std::string str() const;

        template<class T>
        void put(const char *name, T value);

        template<class T>
        T get(const char *name);

        template<class T>
        std::vector <T> getArray(boost::property_tree::ptree::key_type const &key);

        std::vector<Context> getObjects(boost::property_tree::ptree::key_type const &key);

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

#include "context/context_impl.h"
#endif //CONTEXT_INCLUDED
