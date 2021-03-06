#ifndef CONTEXT_INCLUDED
#define CONTEXT_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace templates {
    template <class T>
    struct DefaultSerializer;


    class Context {
    public:
        Context() = default;
        explicit Context(boost::property_tree::ptree &root) : root(root) {};

        explicit Context(const std::string &json);

        template <class T, class Serializer = DefaultSerializer<T>>
        void putArray(const std::string &name, const T * array, size_t count, Serializer serial = Serializer());

        template <class T, class Serializer = DefaultSerializer<T>>
        void putArray(const std::string &name, const std::vector<T> & array, Serializer serial = Serializer());

        inline std::string str() const;

        template<class T>
        void put(const std::string &name, const T &value);

        template<class T>
        T get(const std::string &name) const;

        void set(const std::string & name, const Context & _root);

        template<class T>
        std::vector <T> getArray(boost::property_tree::ptree::key_type const &key) const;

        inline std::vector<Context> getObjects(boost::property_tree::ptree::key_type const &key);

        inline std::unordered_multimap<std::string, std::string> toMap();
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
