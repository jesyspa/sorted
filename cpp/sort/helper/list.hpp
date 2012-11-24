#ifndef HELPER__LIST_H
#define HELPER__LIST_H

#include "node.hpp"
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

            helper::node<T>* head;
            helper::node<T>* tail;
            list(){
                this->len = 0;
                this->head = this->tail = NULL;
            }
            ~list(){
                helper::node<T>* n = this->head;
                if (!n) return;
                helper::node<T>* t = NULL;
                while (n){
                    t = n->next;
                    delete n;
                    n = t;
                }
            }

            // O(n) = constant time, or O(1) as n gets bigger
            int length(){
                return this->len;
            }

            // O(n) = constant time, or O(1) as n gets bigger
            void append(const T& t){
            	helper::node<T>* u = new helper::node<T>(t);
                if (!this->head) {
                    this->head = u;
                    this->tail = u;
                }else {
                    helper::node<T>* v = this->tail;
                    this->tail = u;
                    v->next = u;
                    u->prev = v;
                }
                this->len++;
            }

            T get(const int idx_req){
                helper::node<T>* n = this->head;
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
                helper::node<T>* n = this->head;
                for (int j = 0; j < index; j++) n = n->next;
                helper::node<T>* t = n->prev;
                helper::node<T>* u = n->next;
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

            /* 
                best case: slice of original list at the beginning, taking constant time
                avg case: linear growth, as n gets larger:  O(n) 
                worst case:  still linear growth
            */
            list<T>* slice(int from, int to){
                from = (from < 0) ? 0 : from;
                to = (to > this->len) ? this->len : to;
                list<T>* result = new list<T>();
                helper::node<T> *n = this->head;
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
                helper::node<T>* t = this->head;
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
                helper::node<T>* n = rhs.head;
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
