#!/usr/bin/env python

def merge_sort(coll):
    if len(coll) <= 1:
        return coll
    half = int(len(coll) / 2)
    left = merge_sort(coll[:half])
    right = merge_sort(coll[half:])
    return merge(left, right)

def merge(left, right):
    result = list()
    i ,j = 0, 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]
    return result

import random
coll = [random.randint(1,100) for _ in range(10)]
print ""
print "Unsorted:  ", coll, "\n"
print "Sorted:    ", merge_sort(coll)
