#include "sort/merge.hpp"

#include <iostream>
#include <exception>

int main(int argc, char** argv){
    std::vector<int> v;
    
    // What can this throw?
    try {
        v = sorted::get_random_vector(10, 100);
        std::cout << "Unsorted:  " << v << std::endl;
    } catch(std::exception& e) {
        std::cerr << "get_random_vector(int count,int base) ERROR:  " << e.what() << std::endl;
        return -1;
    }

    // Why are you still trying to sort even when you know you don't have a vector?
    try {
        auto v_sorted = sorted::merge_sort(v);
        std::cout << "Sorted:    " << v_sorted << std::endl;
    } catch(exception& e) {
        std::cerr << "Merge Sort ERROR:  " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
