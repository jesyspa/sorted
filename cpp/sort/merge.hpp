#ifndef MERGE_HPP
#define MERGE_HPP

#include <vector>
#include <utility>
#include <ostream>
#include <cstdlib>
#include <type_traits>

namespace sorted {
    template<typename FwIter1, typename FwIter2, typename OIter>
    OIter merge(FwIter1 b1, FwIter1 e1, FwIter2 b2, FwIter2 e2, OIter o) {
        while (b1 != e1 || b2 != e2) {
            if (b1 != e1 && b2 != e2) {
                if (*b1 < *b2)
                    *o++ = *b1++;
                else
                    *o++ = *b2++;
            } else if (b1 != e1) {
                o = std::copy(b1, e1, o);
                break;
            } else {
                o = std::copy(b2, e2, o);
                break;
            }
        }
        return o;
    }

    template<typename RAIter>
    void merge_sort(RAIter b, RAIter e) {
        if (e - b < 2) return;
        if (e - b == 2) {
            if (b[0] > b[1])
                std::swap(b[0], b[1]);
            return;
        }

        // Homework: why not (2*b - e)/2 + 1?
        auto half = b + (e-b)/2;
        merge_sort(b, half);
        merge_sort(half, e);

        std::vector<typename std::remove_reference<decltype(*b)>::type> result(e-b);
        merge(b, half, half, e, result.begin());
        std::copy(result.begin(), result.end(), b);
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
