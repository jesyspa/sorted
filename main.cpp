#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>
using namespace std;

#include <boost/lexical_cast.hpp>

namespace sorted {

    template<typename T>
    class node {
        public:

            int pos;
            T value;
            node<T>* next;
            node<T>* prev;

            node(const node<T>* t){
            }

            node(const T& t){
                this->next = NULL;
                this->prev = NULL;
                this->value = T(t);
                this->pos = -1;
            }

            node(const T& t, int pos){
                this->next = NULL;
                this->prev = NULL;
                this->value = T(t);
                this->pos = pos;
            }

            ~node(){
                /* pass */
            }

            string dump(){
                return boost::lexical_cast<std::string>(this->value);
            }

        private:
    };

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
                    if (!n) {
                        cout << "list<T>::~list() > n already deleted !!!" << endl;
                        return;
                    } else {
                        cout << "list<T>::~list() > delete n:  " << n->value << endl;
                    }
                    delete n;
                    n = t;
                }
            }

            int length(){
                return this->len;
            }

            void append(const T& t){
                node<T>* u = new node<T>(t, this->len);
                this->tail = u;
                if (!this->head) {
                    this->head = u;
                }else{
                    node<T>* n = this->head;
                    while (n->next) n = n->next; 
                    n->next = u;
                    u->prev = n;
                }
                this->len++;
            }

            T get(const int index){
                node<T>* n = this->head;
                if (index > this->len) throw("Invalid Index!");
                while (n->pos < index) n = n->next;
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
                printf("Removing index=%d, len=%d, ", index, this->len);
                cout << "value: " << n << endl;
                node<T>* t = n->prev;
                node<T>* u = n->next;
                if (u && t){
                    t->next = u;
                    u->prev = t;
                } else if (t){
                    this->tail = t;
                } else if (u){
                    this->head = u;
                }
                cout << "list<T>::remove() > Deleting n" << endl;
                delete n;
                this->len--;
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
                long result_addr = (long)&rhs;
                node<T>* n = rhs.head;
                while (n->next) {
                    cout << n->value << endl;
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

    template<typename T>
    list<T>* merge(list<T>* left, list<T>* right){
        list<T>* result = new list<T>();
        while ((left->length() > 0) || (right->length() > 0)){
            if ((left->length() > 0) && (right->length() > 0)){
                T l = left->get(0);
                T r = right->get(0);
                if (l <= r){
                    result->append(l);
                    left->remove(0);
                } else{
                    result->append(r);
                    right->remove(0);
                }
            } else if (left->length() > 0){
                result->append(left->get(0));
                left->remove(0);
            } else if (right->length() > 0){
                result->append(right->get(0));
                right->remove(0);
            }
        }
        cout << "Deleting left:  " << left << endl;
        delete left;
        cout << "Deleting right:  " << right << endl;
        delete right;
        return result;
    }

    template<typename T>
    list<T>* merge_sort(list<T>* original){
        if (original->length() == 1) return original;
        int len = original->length();
        list<T>* left = new list<T>();
        list<T>* right = new list<T>();
        if (len > 2){
            left = original->slice(0,(len/2));
            right = original->slice((len/2)+1,len-1);
        }else if (len == 2){
            left = original->slice(0,0);
            right = original->slice(1,1);
        }
        cout << "Left:  " << left << endl;
        cout << "Right:  " << left << endl;
        left = merge_sort(left);
        right = merge_sort(right);
        return merge(left, right);
    }
}

sorted::list<int>* get_random_list(){
    sorted::list<int>* l = new sorted::list<int>();
    srand(time(NULL));
    for (int i = 0; i < 10; i++) l->append(rand() % 100);
    return l;
}

int main(int argc, char** argv){
    sorted::list<int>* l = get_random_list();
    cout << "Original:     " << l << endl; 
    sorted::list<int>* l_after_sort = sorted::merge_sort(l);
    cout << "Sorted:       " << l_after_sort << endl;
    delete l;
    delete l_after_sort;
    return 0;
}
