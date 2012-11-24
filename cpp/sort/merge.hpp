#include "helper/list.hpp"

namespace sorted {

    template<typename T>
    helper::list<T>* merge(helper::list<T>* left, helper::list<T>* right){
        helper::list<T>* result = new helper::list<T>();
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
    helper::list<T>* merge_sort(helper::list<T>* original){
        if (original->length() <= 1) {
            return original;
        }
        int len = original->length();
        helper::list<T>* left = NULL;
        helper::list<T>* right = NULL;
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
        helper::list<T>* result = merge(left, right);
        delete left;
        delete right;
        return result;
    }

    helper::list<int>* get_random_list(int count, int base){
        helper::list<int>* l = new helper::list<int>();
        srand(time(NULL));
        for (int i = 0; i < count; i++) l->append(rand() % base);
        return l;
    }
}

