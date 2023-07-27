/*!
 * \file
 * Functions for file parsing
 */
#include "file_parser.h"
#include <assert.h>
#include <bits/types/wint_t.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <wchar.h>

ssize_t getByteSize(FILE* pFile)
{
    if (fileno(pFile) == -1) {
        perror("Couldn't get the file's descriptor!\n");
        return -1;
    }

    struct stat buffer;

    if (fstat(fileno(pFile), &buffer) != 0) {
        perror("Couldn't create the fstat struct!\n");
        return -1;
    }

    return buffer.st_size;
}

arrayLines readToLines(FILE *pFile)
{
    size_t byte_size = getByteSize(pFile);

    // Allocate memory for all chars form the file
    wchar_t* text = (wchar_t*)calloc(byte_size + sizeof(L'\0'), sizeof(wchar_t));

    // Fill the array by file's content
    wint_t wc = L'\0';
    size_t number_lines = 0;
    for (size_t i = 0; (wc = fgetwc(pFile)) != WEOF; i++) {
        if (wc == L'\n') {
            *(text + i) = L'\0';
            ++number_lines;
            continue;
        }
        *(text + i) = wc;
    }

    // Allocate memory for array of pointers to text's lines
    line* lines = (line*)calloc(number_lines, sizeof(line));

    // Fill the array of lines
    for (size_t line_index = 0, text_index = 0, line_len = 0; line_index < number_lines; text_index++) {
        if (line_len == 0) {
            lines[line_index].content = &text[text_index];
        }
        if (text[text_index] == L'\0') {
            lines[line_index].length = line_len;
            ++line_index;
            line_len = 0;
        }
        else {
            ++line_len;
        }
    }

    return {lines, number_lines};
}

void addToFile(arrayLines array, FILE* pFile)
{
    for (size_t i = 0; i < array.size; i++)
        fwprintf(pFile, L"%ls\n", array.lines[i].content);
}

// NOTE: wtf
// ssize_t getSymbolsNumber(FILE* pFile)
// {
//     if (fseek(pFile, 0L, SEEK_END) != 0) {
//         perror("Could't seek the end of the file");
//         return 0;
//     }

//     size_t symbols_number = ftell(pFile);

//     if (fseek(pFile, 1L, SEEK_SET) != 0 || fseek(pFile, 0L, SEEK_SET) != 0) {
//         perror("Could't seek the beginning of the file");
//         return 0;
//     }

//     return symbols_number;
// }
