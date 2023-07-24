#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include <stddef.h>
#include <stdio.h>

void swap(char* a, char* b, size_t size);

void quick_sort(void* const base, size_t total_elements, size_t size, int (*compare)(const void*, const void*));

ssize_t partition(char* const base, size_t size, ssize_t lo, ssize_t hi, int (*compare)(const void*, const void*));

#endif // QUICK_SORT_H_
