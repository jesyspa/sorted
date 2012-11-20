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
        node<T>* head;
        node<T>* tail;
        int len;
    public:
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
                this->tail = u;
            }else{
                node<T>* n = this->head;
                if (!n) return;
                while (n->next) n = n->next; 
                n->next = u;
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
            for (int j = 0; j < index; j++) n = n->next;
            if (n->prev && n->next){
                n->prev->next = n->next;
                n->next->prev = n->prev;
            } else if (n->prev){
                this->tail = n->prev;
            } else if (n->next){
                this->head = n->prev;
            }
            this->len--;
        }

        list<T>* slice(int* from, int* to){
            from =  ((from == NULL) || (from < 0           )) ?            new int(0) : from;
            to =    ((  to == NULL) || (  to > this->len)) ? new int(this->len) : to;
            list<T>* t = new list<T>();
            for (int i = 0; i < this->len; i++){
                if ((i > *from) && (i < *to)) t.append(this->get(i));
                if (i > *to) break;
            }
        }

        ostream& operator<<(ostream &o, const list<T>& l) {
            node<T>* t = l.head;
            while (t){
                strm << *(t->value);
                if (!t->next) break;
                strm << ", ";
                t = t->next;
            }
            return strm;
        }
};

template<typename T>
list<T> merge_sort(list<T> coll){
    if (coll.length() == 1){
        return coll;
    }
    // list<T>* left, right, result;
    // left = merge_sort(left);
    // right = merge_sort(right);
    // while ((left->length > 0) || (right->length > 0)){
    //     if ((left->length > 0) && (right->length > 0)){
    //         if (*(left->head->value) <= *(right->head->value)){
    //             result.append(left.
    //             left = rest(left)
    //         }else{
    //             append first(right) to result
    //             right = rest(right)
    //         }
    //     }else if (left->length > 0) {
    //     }else if (right->length > 0) {
    //     }
    // }
    return coll;
}

int main(int argc, char** argv){
    list<int> l;
    l.append(5);
    l.append(6);
    cout << l.get(0) << endl;
    cout << l << endl;
    l.remove(0);
    cout << l << endl;
    return 0;
}
