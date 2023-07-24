#ifndef LEXICOGRAPHIC_SORT_H_
#define LEXICOGRAPHIC_SORT_H_

#include "file_parser.h"

int compareLexicographically(void *const _str1, void *const _str2, int order);

int compareLexicographicallyForward(void *const str1, void *const str2);

int compareLexicographicallyBackward(void *const str1, void *const str2);

void alphabetize(arrayLines lines, int order);

#endif // LEXICOGRAPHIC_SORT_H_
