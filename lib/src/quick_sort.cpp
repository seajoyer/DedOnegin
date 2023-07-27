#include "quick_sort.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

const size_t THRESHOLD = 2;

// TODO: More efficient way to swap
void swap(char *a, char *b, size_t size)
{
    do {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    } while (--size > 0);
}

size_t partition(char *const base, size_t size, size_t lo, size_t hi, int (*compare)(const void*, const void*))
{
    size_t i = lo, j = hi;
    char *pivot = (base + ((hi + lo) / 2) * size);

    do {
        while (base + i * size != pivot && compare(base + i * size, pivot) < 0) i++;
        while (base + j * size != pivot && compare(base + j * size, pivot) > 0) j--;

        if (i >= j)
            return j;

        swap(base + i * size, base + j * size, size);

        if (base + i * size == pivot)
            pivot = base + j * size;
        else if (base + j * size == pivot)
            pivot = base + i * size;

        ++i;
        --j;

    } while (true);
}

void quick_sort(void *const base, size_t total_elements, size_t size, int (*compare)(const void*, const void*))
{
    if (total_elements < THRESHOLD)
        return;

    char   *const pBase = (char *const) base;
    size_t const pivot_index = partition(pBase, size, 0, total_elements - 1, compare);
    char   *const pivot = pBase + pivot_index * size;

    if (pivot_index + 1 < total_elements) //< +1 because indexes are enumerated from 0
        quick_sort(pivot + size, total_elements - (pivot_index + 1), size, compare);

    quick_sort(base, pivot_index + 1, size, compare);
}
