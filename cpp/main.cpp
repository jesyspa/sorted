#include <iostream>
using namespace std;

#include "sort/merge.hpp"

int main(int argc, char** argv){
    std::vector<int> v = sorted::get_random_vector(10, 100);
    cout << "Unsorted:  " << v << endl;
    std::vector<int> v_sorted = sorted::merge_sort(v);
    cout << "Sorted:    " << v_sorted << endl;
    return 0;
}
