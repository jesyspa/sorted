#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>
using namespace std;

template<typename T>
class node {
    public:

        int pos;
        T* value;
        node<T>* next;
        node<T>* prev;

        node(const T& t){
        	this->next = NULL;
        	this->prev = NULL;
        	this->value = new T(t);
            this->pos = -1;
        }

        node(const T& t, int pos){
        	this->next = NULL;
        	this->prev = NULL;
        	this->value = new T(t);
            this->pos = pos;
        }

        ~node(){
            if (this->value) delete this->value;
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
            this->head = this->tail = 0;
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
            return *(n->value);
        }

        void remove(const int& index){
            if ((index < 0) || (index > this->len)){
                throw("Invalid index");
            }
            node<T>* n = this->head;
            for (int j = 0; j < index; j++) {
                // cout << "  ["<< j << "] Moving to next:  " << n << endl;
                n = n->next;
            }
            // cout << "Found index: " << index << ", node=" << n << endl;
            node<T>* t = n->prev;
            node<T>* u = n->next;
            if (u && t){
                // cout << "next=" << t << ", prev=" << u << endl;
                t->next = u;
                u->prev = t;
            } else if (t){
                // cout << "next=" << t << endl;
                this->tail = t;
            } else if (u){
                // cout << "prev=" << u << endl;
                this->head = u;
            }
            delete n;
            this->len--;
        }

        list<T>* slice(int from, int to){
            from = (from < 0) ? 0 : from;
            to = (to > this->len) ? this->len : to;
            list<T>* t = new list<T>();
            node<T>* n = this->head;
            int i = 0;
            while (n && (i < this->len)){
                if ((from <= i) && (i <= to))
                    t->append(*n->value);
                n = n->next;
                i++;
            }
            return t;
        }

};

template <class T>
ostream& operator<<(ostream &o, const list<T>* l) {
    node<T>* t = l->head;
    o << "[";
    while (t){
        o << t;
        if (!t->next) break;
        o << ", ";
        t = t->next;
    }
    o << "]";
    return o;
};

template <class T>
ostream& operator<<(ostream &o, const node<T>* n) {
    o << *(n->value);
    return o;
};

template<typename T>
list<T>* merge_sort(list<T>* coll){
    if (coll->length() == 1){
        return coll;
    }
    // list<T>* left, right, result;
    // cout << *left << endl;
    // cout << right << endl;
    // left = merge_sort(left);
    // right = merge_sort(right);
    return coll;
}

int main(int argc, char** argv){
    list<int>* l = new list<int>();
    srand(time(NULL));
    for (int i = 0; i < 10; i++) l->append(rand() % 100);
    cout << "Original:  " << l << endl; 
    l = merge_sort(l);
    // cout << "Calling lst->remove(" << (l->length()-2) << ")" << endl;
    list<int> *l2 = l->slice(0,4);
    cout << "Sorted:    " << l << endl;
    cout << "Sliced:    " << l2 << endl;
    delete l;
    delete l2;
    return 0;
}
