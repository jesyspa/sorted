#ifndef HELPER__NODE_H
#define HELPER__NODE_H

#include <iostream>
#include <string>
using namespace std;

#include <boost/lexical_cast.hpp>

namespace sorted {

    template<typename T>
    class node {
        public:
            T value;
            node<T>* next;
            node<T>* prev;
            node(const node<T>* t){
                this->value = T(t->value);
            }
            node(const T& t){
                this->next = NULL;
                this->prev = NULL;
                this->value = T(t);
            }
            string dump(){
                return boost::lexical_cast<std::string>(this->value);
            }
    };

    template <class T>
    ostream& operator<<(ostream &o, const node<T>& n) {
        o << n.dump();
        return o;
    };

    template <class T>
    ostream& operator<<(ostream &o, const node<T>* n) {
        o << n->dump();
        return o;
    };

}

#endif
