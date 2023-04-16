#include "sorting_algorithms.h"
#include "ansi_colors.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const size_t THRESHOLD = 2; //! The smallest number of elements to sort

void swap(char* a, char* b, size_t size)
{
    do {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    } while (--size > 0);
}

void quick_sort(void* const base, size_t total_elements, size_t size, int (*compare)(const void*, const void*))
{
    if (total_elements < THRESHOLD)
        return;

    char* base_ptr = (char*)base;

    size_t lo = 0;
    size_t hi = total_elements - 1;

    char* pivot = base_ptr + size * (total_elements / 2);

    while (lo <= hi) {
        while (compare(base_ptr + lo * size, pivot) < 0) ++lo;
        while (compare(base_ptr + hi * size, pivot) > 0) --hi;
        if (lo > hi)
            break;

        swap(base_ptr + lo * size, base_ptr + hi * size, size);

        if (base_ptr + lo * size == pivot || base_ptr + hi * size == pivot) {
            if (base_ptr + lo * size == pivot)
                pivot = base_ptr + hi * size;
            else if (base_ptr + hi * size == pivot)
                pivot = base_ptr + lo * size;
        }

        ++lo;
        --hi;
    }

    quick_sort(base_ptr, hi + 1, size, compare);
    quick_sort(base_ptr + lo * size, total_elements - lo, size, compare);
}
