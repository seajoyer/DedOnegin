#ifndef LEXICOGRAPHIC_SORT_H_
#define LEXICOGRAPHIC_SORT_H_

#include "file_parser.h"

int compareLexicographically(const line line1, const line line2, int order);

int compareLexicographicallyForward(const void* pLine1, const void* pLine2);

int compareLexicographicallyBackward(const void* pLine1, const void* pLine2);

void alphabetize(arrayLines array, int order);

#endif // LEXICOGRAPHIC_SORT_H_
