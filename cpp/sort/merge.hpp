#ifndef MERGE_HPP
#define MERGE_HPP

#include <vector>
#include <utility>
#include <cstdlib>             /* srand()  */
#include <ctime>               /* time()   */

// I'm surprized this doesn't already exist.  Or, 
// more likey, I'm doing this wrong.  lol.  
template <typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T> const& v) {
    unsigned int i = 0;
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
};

namespace sorted {

    // This could better be done with iterator ranges.
    // Also, vectors aren't the best data structure to use within the sort; a deque would
    // offer better performance.  I suspect this might not really be O(n*log(n))
    template<typename T>
    std::vector<T> merge(std::vector<T> left, std::vector<T> right) {
        std::vector<T> result;
        result.reserve(left.size() + right.size());
        while (left.size() || right.size()) {
            if (left.size() && right.size()) {
                if (left.front() <= right.front()) {
                    result.push_back(left.front());
                    left.erase(left.begin());
                } else {
                    result.push_back(right.front());
                    right.erase(right.begin());
                }
            } else if (!left.empty()) {
                result.push_back(left.front());
                left.erase(left.begin());
            } else if (!right.empty()) {
                result.push_back(right.front());
                right.erase(right.begin());
            }
        }
        return result;
    }

    template<typename T>
    std::vector<T> merge_sort(std::vector<T> in){

        size_t len = in.size();

        if (len < 2) return in;

        std::vector<T> left, right;

        if (in.size() > 2){
            left = std::vector<T>(in.begin(), in.begin() + (len / 2));
            right = std::vector<T>(in.begin() + (len / 2), in.end());
        } else {
            left.push_back(in[0]);
            right.push_back(in[1]);
        }

        left = merge_sort(std::move(left));
        right = merge_sort(std::move(right));

        std::vector<T> out = merge(std::move(left), std::move(right));
        return out;
    }

    std::vector<int> get_random_vector(int count, int base) {
        std::vector<int> v(count);
        // Why not use the C++11 facilities?
        for (auto& e : v)
            e = rand() % base;
        return v;
    }
}

#endif
