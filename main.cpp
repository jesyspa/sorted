#include <iostream>
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
        node<T>* head;
        node<T>* tail;
        int length;
    public:
        list(){
            this->length = 0;
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

        int get_length(){
            return this->length;
        }

        void push(const T& t){
            node<T>* u = new node<T>(t, this->length);
            this->tail = u;
            if (!this->head) {
                this->head = u;
                this->tail = u;
            }else{
                node<T>* n = this->head;
                if (!n) return;
                while (n->next) n = n->next; 
                n->next = u;
            }
            this->length++;
        }

        T get(const int index){
            node<T>* n = this->head;
            if (index > this->length) throw("Invalid Index!");
            while (n->pos < index) n = n->next;
            return *(n->value);
        }

        T pop(){
            if (!this->tail) throw("Invalid Operation:  No value to return.");
            if (!this->tail->prev) return *(this->tail->value);
            this->tail = this->tail->prev;
            return *(this->tail->value);
        }

        list<T>* slice(int* from, int* to){
            from =  ((from == NULL) || (from < 0         )) ? new int(0)               : from;
            to =    ((  to == NULL) || (to > this->length)) ? new int(this->length)    : to;
            list<T>* t = new list<T>();
            for (int i = 0; i < this->length; i++){
                if ((i > from) && (i < to))
                    t.push(this->get(i));
                else if (i > to) break;
            }
        }

};

template<typename T>
list<T>* merge_sort(list<T>* coll){
    if (coll->get_length() == 1){
        return coll;
    }
    list<T>* left, right;
    left = coll->slice(coll->
}

int main(int argc, char** argv){
    list<int>* l = new list<int>();
    l->push(5);
    cout << l->get(0) << endl;
    cout << l->get_length() << endl;
    delete l;
    return 0;
}
