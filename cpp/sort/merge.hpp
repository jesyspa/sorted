#include "helper/list.hpp"

namespace sorted {

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
                continue;
            }

            if (left->length() > 0) {
                result->append(left->get(0));
                left->remove(0);
            }

            if (right->length() > 0) {
                result->append(right->get(0));
                right->remove(0);
            }
        }
        return result;
    }

    template<typename T>
    list<T>* merge_sort(list<T>* original){
        if (original->length() <= 1) {
            return original;
        }
        int len = original->length();
        list<T>* left = NULL;
        list<T>* right = NULL;
        if (len > 2){
            left = original->slice(0,(len/2));
            right = original->slice((len/2)+1,len-1);
        }else if (len == 2){
            left = original->slice(0,0);
            right = original->slice(1,1);
        }
        left = merge_sort(left);
        right = merge_sort(right);
        delete original;
        list<T>* result = merge(left, right);
        delete left;
        delete right;
        return result;
    }

    list<int>* get_random_int_list(int count, int base){
        sorted::list<int>* l = new sorted::list<int>();
        srand(time(NULL));
        for (int i = 0; i < count; i++) l->append(rand() % base);
        return l;
    }
}

