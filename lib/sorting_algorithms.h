#ifndef SORTING_ALGORITHMS_H_
#define SORTING_ALGORITHMS_H_

#include <stddef.h>

void swap(char* a, char* b, size_t size);

void quick_sort(void* const base, size_t total_elements, size_t size, int (*compare)(const void*, const void*));

#endif // SORTING_ALGORITHMS_H_
