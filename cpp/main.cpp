#include <iostream>
using namespace std;

#include "sort/helper/list.hpp"
#include "sort/merge.hpp"

int main(int argc, char** argv){
    helper::list<int>* l = sorted::get_random_list(10, 100);
    cout << "Unsorted:  " << l << endl;
    l = sorted::merge_sort(l);
    cout << "Sorted:    " << l << endl;
    for (int i = 0; i < (l->length() - 1); i++){
        int t = l->get(i);
        int u = l->get(i+1); 
        if (t > u){
            helper::list<int>* m = l->slice(i - 5, i + 5);
            cout << "Failed to sort properly:  " << m << endl;
            delete m;
            break;
        }
    }
    delete l;
    return 0;
}
