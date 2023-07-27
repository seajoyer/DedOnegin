// TODO: doc

#include "file_parser.h"
#include "lexicographic_sort.h"
#include "quick_sort.h"
#include <assert.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void addInitialToFile(FILE* pFile, wchar_t* init, size_t numberLines)
{
    fwprintf(pFile, L"%ls\n", init);

    for (size_t text_index = 1, line_index = 1; line_index < numberLines; text_index++) {

        if (init[text_index] == L'\0') {
            fwprintf(pFile, L"%ls\n", init + text_index + 1);
            ++line_index;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    FILE* src_file = fopen("Eugene-Onegin.txt", "r");
    if (!src_file) {
        perror("Couldn't read the file!\n");
        return -1;
    }

    arrayLines array_lines = readToLines(src_file);

    fclose(src_file);


    FILE* out_file = fopen("out.txt", "w");
    if (!out_file) {
        perror("Couldn't write to the file!\n");
        return -1;
    }

    wchar_t* init = array_lines.lines[0].content; //< Beginning of the initial text

    alphabetize(array_lines, +1);
    addToFile  (array_lines, out_file);

    alphabetize(array_lines, -1);
    addToFile  (array_lines, out_file);

    free(array_lines.lines);

    addInitialToFile(out_file, init, array_lines.size);

    fclose(out_file);

    free(init);

    return 0;
}
