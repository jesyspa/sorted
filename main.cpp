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
                return T(n->value);
            }

            void remove(const int& index){
                if ((index < 0) || (index > this->len)) throw("Invalid index");
                node<T>* n = this->head;
                for (int j = 0; j < index; j++) n = n->next;
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
                delete n;
                this->len--;
            }

            list<T> slice(int from, int to){
                from = (from < 0) ? 0 : from;
                to = (to > this->len) ? this->len : to;
                list<T> result;
                node<T> *n = this->head;
                int idx = 0;
                printf("from=%d, to=%d\n", from, to);
                while (n && (idx < this->len)){
                    if ((from <= idx) && (idx <= to)) result.append(n->value);
                    if (idx > to) break;
                    cout << "slicing (" << idx << "):  " << result << endl;
                    n = n->next;
                    idx++;
                }
                cout << result << endl;
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
    list<T> merge_sort(list<T> original){
        cout << original << endl;
        if (original.length() == 1) return original;
        int len = original.length();
        list<T> result = original.slice(0,(len/2));
        cout << "Slice:  " << result << endl;
        return result;
    }

}

int main(int argc, char** argv){
    sorted::list<int> l;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) l.append(rand() % 100);
    cout << "Original:  " << l << endl; 
    l = sorted::merge_sort(l);
    cout << l << endl;
    return 0;
}
