#include <iostream>
#include <exception>
using namespace std;

#include "sort/merge.hpp"

int main(int argc, char** argv){

    vector<int> v;

    try{
        v = sorted::get_random_vector(10, 100);
        cout << "Unsorted:  " << v << endl;
    }catch(exception& e){
        cerr << "get_random_vector(int count,int base) ERROR:  " << e.what() << endl;
        return -1;
    }

    try{
        vector<int> v_sorted = sorted::merge_sort(v);
        cout << "Sorted:    " << v_sorted << endl;
    }catch(exception& e){
        cerr << "Merge Sort ERROR:  " << e.what() << endl;
        return -1;
    }

    return 0;
}
