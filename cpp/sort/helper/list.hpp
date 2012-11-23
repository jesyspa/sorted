#ifndef HELPER__LIST_H
#define HELPER__LIST_H

#include <iostream>
#include <string>
using namespace std;

#include <boost/lexical_cast.hpp>

namespace helper {

    template<typename T>
    class list {
        private:
            int len;
        public:

            node<T>* head;
            node<T>* tail;
            list(){
                this->len = 0;
                this->head = this->tail = NULL;
            }
            ~list(){
                node<T>* n = this->head;
                if (!n) return;
                node<T>* t = NULL;
                while (n){
                    t = n->next;
                    delete n;
                    n = t;
                }
            }

            int length(){
                return this->len;
            }

            void append(const T& t){
            	node<T>* u = new node<T>(t);
                this->tail = u;
                if (!this->head) {
                    this->head = u;
                }else{
                    node<T>* n = this->head;
                    while (n->next) n = n->next; 
                    n->next = u;
                    u->prev = n;
                    this->tail = u;
                }
                this->len++;
            }

            T get(const int idx_req){
                node<T>* n = this->head;
                if ((idx_req > this->len) || (idx_req < 0)) throw("Invalid Index!");
                int idx = 0;
                while (idx < idx_req) {
                    n = n->next;
                    idx++;
                }
                return T(n->value);
            }

            void remove(const int& index){
                if ((index < 0) || (index > this->len)) {
                    cout << "Invalid index:  " << index << endl;
                    return;
                } else {
                }
                node<T>* n = this->head;
                for (int j = 0; j < index; j++) n = n->next;
                node<T>* t = n->prev;
                node<T>* u = n->next;
                if (u && t){
                    t->next = u;
                    u->prev = t;
                } else if (t){
                    t->next = NULL;
                    this->tail = t;
                } else if (u){
                    u->prev = NULL;
                    this->head = u;
                } 
                delete n;
                this->len--;
                if (this->len == 0) this->head = this->tail = NULL;
                if (this->len == 1) {
                    if (u) this->head = this->tail = u;
                    else if (t) this->head = this->tail = t;
                }
            }

            list<T>* slice(int from, int to){
                from = (from < 0) ? 0 : from;
                to = (to > this->len) ? this->len : to;
                list<T>* result = new list<T>();
                node<T> *n = this->head;
                int idx = 0;
                while (n && (idx < this->len)){
                    if ((from <= idx) && (idx <= to)) result->append(n->value);
                    if (idx > to) break;
                    n = n->next;
                    idx++;
                }
                return result;
            }

            string dump(){
                node<T>* t = this->head;
                string d = "";
                d += "[";
                while (t){
                    d += t->dump();
                    if (!t->next) break;
                    d += ", ";
                    t = t->next;
                }
                d += "]";
                return d;
            }

            list<T>& operator= (const list<T>& rhs){
                node<T>* n = rhs.head;
                while (n->next) {
                    this->append(T(n->value));
                    n = n->next;
                }
                return *this;
            }

    };

    template <class T>
    ostream& operator<<(ostream &o, list<T>& l) {
        o << l.dump();
        return o;
    };

    template <class T>
    ostream& operator<<(ostream &o, list<T>* l) {
        o << l->dump();
        return o;
    };
}

#endif
