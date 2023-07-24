#include "quick_sort.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

// TODO: check for size_t and ssize_t

const size_t THRESHOLD = 2;

void swap(char *a, char *b, size_t size)
{
    do {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    } while (--size > 0);
}

ssize_t partition(char *const base, size_t size, ssize_t lo, ssize_t hi, int (*compare)(const void*, const void*))
{
    ssize_t i = lo, j = hi;
    // printf("lo = %zu, hi = %zu\n", lo, hi);
    char *pivot = (base + ((hi + lo) / 2) * size);
    // printf("pivot = %p\n", pivot);
    do {
        while (base + i * size != pivot && compare(base + i * size, pivot) < 0) i++;
        while (base + j * size != pivot && compare(base + j * size, pivot) > 0) j--;

        if (i >= j)
            return j;

        swap(base + i * size, base + j * size, size);

        // printf("\n");
        // for (ssize_t k = lo; k < hi - lo + 1; k++)
        //     printf("%zu) %ls\n", k, *(wchar_t* const*) (void *const) (base + k * size));

        // printf("+ i = %ls | + j = %ls\n", *(wchar_t* const*) (void *const) (base + i * size), *(wchar_t* const*) (void *const) (base + j * size));

        if (base + i * size == pivot)
            pivot = base + j * size;
        else if (base + j * size == pivot)
            pivot = base + i * size;
        // printf("pivot = %ls\n", *(wchar_t* const*) (void *const) (pivot));
        // printf("\n");
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
    // printf("\nbase = %ls\n", *(wchar_t* const*)(void* const)(base));
    // if (pivot_index + 1 < total_elements)
    //     printf("pivot + size = %ls\n", *(wchar_t* const*)(void* const)(pivot + size));

    if (pivot_index + 1 < total_elements) // +1 because indexes are enumerated from 0
        quick_sort(pivot + size, total_elements - (pivot_index + 1), size, compare);
    quick_sort(base, pivot_index + 1, size, compare);
}
