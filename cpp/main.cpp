#include <iostream>;
using namespace std;

int main(int argc, char** argv){
    sorted::list<int>* l = get_random_list();
    l = merge_sort(l);
    for (int i = 0; i < (l->length() - 1); i++){
        int t = l->get(i);
        int u = l->get(i+1); 
        if (t > u){
            sorted::list<int>* m = l->slice(i - 5, i + 5);
            cout << m << endl;
            delete m;
            break;
        }
    }
    delete l;
    return 0;
}
