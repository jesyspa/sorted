#include "sort/merge.hpp"

#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>

// I'm surprized this doesn't already exist.  Or,
// more likey, I'm doing this wrong.  lol.
template <typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T> const& v) {
    o << "[";
    bool first = true;
    for (auto const& e : v) {
        if (!first)
            o << ", ";
        o << e;
        first = false;
    }
    o << "]";
    return o;
}

int main() {
    std::vector<int> v;
    std::srand(static_cast<unsigned int>(std::time(0)));


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
        sorted::merge_sort(v.begin(), v.end());
        std::cout << "Sorted:    " << v << std::endl;
    } catch(std::exception& e) {
        std::cerr << "Merge Sort ERROR:  " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
