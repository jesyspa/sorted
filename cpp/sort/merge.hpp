
#ifndef MERGE_HPP
#define MERGE_HPP

#include <stdlib.h>             /* srand()  */
#include <time.h>               /* time()   */
#include "helper/list.hpp"

namespace sorted {

    // O(n), this method will grow in run-time linearly, as n gets bigger
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

    // the complexity of this method depends on the complexity of 
    // both slice and merge operations.  Slicing is O(n*log n) 
    // and merging grows linearly which is O(n).  
    //
    // Conclusion:  merge_sort is O(n + n*log n) which boils
    // down to O(n*log n) 
    //
    // for an explanation of how dividing the problem in half
    // each time turns into log-based-two of n, see the following
    // article:  http://www.crsr.net/Notes/BigO.html
    template<typename T>
    helper::list<T>* merge_sort(helper::list<T>* original){
        int len = original->length();
        helper::list<T>* left = NULL;
        helper::list<T>* right = NULL;
        if (len < 2){
            return original;
        } else if (len == 2){
            left = original->slice(0,0);
            right = original->slice(1,1);
        } else if (len > 2){
            left = original->slice(0,(len/2));
            right = original->slice((len/2)+1,len-1);
        }
        left = merge_sort(left);
        right = merge_sort(right);
        delete original;
        helper::list<T>* result = merge(left, right);
        delete left;
        delete right;
        return result;
    }

    /*
        O(n) - linear growth as input size grows
    */
    helper::list<int>* get_random_list(int count, int base){
        helper::list<int>* l = new helper::list<int>();
        srand(time(NULL));
        for (int i = 0; i < count; i++) l->append(rand() % base);
        return l;
    }
}

#endif
