#include "lexicographic_sort.h"
#include "file_parser.h"
#include "quick_sort.h"
#include <assert.h>
#include <bits/types/wint_t.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

int compareLexicographically(const line line1, const line line2, int order)
{
    size_t ind1 = 0;
    size_t ind2 = 0;

    if (order < 0) {
        ind1 = line1.length - 1;
        ind2 = line2.length - 1;
    }
    else if (order == 0) {
        perror("Unexpected order!\n");
        return 0;
    }

    wchar_t wc1 = L'\0';
    wchar_t wc2 = L'\0';

    while (ind1 >= 0 && ind2 >= 0) {

        wc1 = line1.content[ind1];
        wc2 = line2.content[ind2];

        if (wc1 == L'\0' || wc2 == L'\0')
            break;

        else if (!iswalpha(wc1))
                ind1 += order;
        else if (!iswalpha(wc2))
                ind2 += order;

        else if (towlower(wc1) != towlower(wc2))
            break;

        else {
            ind1 += order;
            ind2 += order;
        }
    }

    // printf("\n\n\n%ls | %d | %zu\n%ls | %d | %zu\n\n\n", line1.content, wc1, ind1, line2.content, wc2, ind2);

    return towlower(wc1) - towlower(wc2);
}

int compareLexicographicallyForward(const void* pLine1, const void* pLine2)
{
    const line line1 = *(const line*)pLine1;
    const line line2 = *(const line*)pLine2;
    return compareLexicographically(line1, line2, +1);
}

int compareLexicographicallyBackward(const void* pLine1, const void* pLine2)
{
    const line line1 = *(const line*)pLine1;
    const line line2 = *(const line*)pLine2;
    return compareLexicographically(line1, line2, -1);
}

void alphabetize(arrayLines array, int order)
{
    if (order > 0)
        quick_sort(array.lines, array.size, sizeof(line), compareLexicographicallyForward);

    if (order < 0)
        quick_sort(array.lines, array.size, sizeof(line), compareLexicographicallyBackward);
}
