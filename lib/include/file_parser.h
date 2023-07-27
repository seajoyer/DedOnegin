#ifndef TEXT_PARSER_H_
#define TEXT_PARSER_H_

#include <cstddef>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wchar.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
    wchar_t* content;
    size_t length;
} line;

typedef struct {
    line*  lines;
    size_t size;
} arrayLines;

ssize_t    getByteSize(FILE* pFile);

arrayLines readToLines(FILE *pFile);

void       addToFile(arrayLines lines, FILE* pFile);

#endif // TEXT_PARSER_H_
