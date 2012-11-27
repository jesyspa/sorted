
#ifndef MERGE_HPP
#define MERGE_HPP

#include <vector>
#include <stdlib.h>             /* srand()  */
#include <time.h>               /* time()   */

template <class T>
ostream& operator<<(ostream &o, vector<T> v) {
    unsigned int i = 0;
    o << "[";
    for (i=0; i < v.size(); i++) {
        o << v[i];
        if (i < v.size() - 1) {
            o << ", ";  
        }
    }
    o << "]";
    return o;
};

namespace sorted {


    template<typename T>
    vector<T> merge(vector<T> left, vector<T> right){
        vector<T> result;
        result.reserve(left.size() + right.size());
        cout << "left=" << left << ", right=" << right << endl;
        while (left.size() || right.size()){
            if (left.size() && right.size()){
                if (left.front() <= right.front()){
                    cout << "Pushing " << left.front() << endl;
                    result.push_back(left.front());
                    left.erase(left.begin());
                } else {
                    cout << "Pushing " << right.front() << endl;
                    result.push_back(right.front());
                    right.erase(right.begin());
                }
            }else if (right.empty()){
                result.push_back(left.front());
                left.erase(left.begin());
            }else if (left.empty()){
                result.push_back(right.front());
                right.erase(right.begin());
            }
        }
        cout << "result:  " << result << endl;
        return result;
    }

    template<typename T>
    std::vector<T> merge_sort(std::vector<T> in){

        size_t len = in.size();

        if (len < 2) return in;

        std::vector<T> left;
        std::vector<T> right;

        if (in.size() > 2){
            left = std::vector<T>(in.begin(), in.begin() + (len / 2));
            right = std::vector<T>(in.begin() + ((len / 2) + 1) , in.begin() + (len - 1));
        } else {
            left = std::vector<T>(in[0]);
            right = std::vector<T>(in[1]);
        }
        cout << "left=" << left << ", right=" << right << endl;

        left = merge_sort(left);
        right = merge_sort(right);

        std::vector<T> out = merge(left,right);
        return out;
    }


    std::vector<int> get_random_vector(int count, int base){
        std::vector<int> array(count);
        srand(time(NULL));
        for (int i = 0; i < count; i++) array[i] = rand() % base;
        return array;
    }
}

#endif
