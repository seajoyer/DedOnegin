#include "file_parser.h"
#include <assert.h>
#include <limits.h>
#include <string.h>

//! '\n' is ignored
int min_line_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    char character;
    size_t min_length = ULONG_MAX, min_line_index = 0;
    for (size_t i = 0, line_index = 0; (character = fgetc(file_pointer)) != EOF; i++) {
        if (character == '\n') {
            if (i < min_length) {
                min_length = i;
                min_line_index = line_index;
            }
            i = 0;
            ++line_index;
        }
    }
    return min_line_index;
}

//! '\n' is ignored
int max_line_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    char character;
    size_t max_length = 0, max_line_index = 0;
    for (size_t i = 0, line_index = 0; (character = fgetc(file_pointer)) != EOF; i++) {
        if (character == '\n') {
            if (i > max_length) {
                max_length = i;
                max_line_index = line_index;
            }
            i = 0;
            ++line_index;
        }
    }
    return max_line_index;
}

int min_line_length_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    int min_length = 0, current_length = 0, character;

    while ((character = fgetc(file_pointer)) != '\n')
        ++min_length;

    while ((character = fgetc(file_pointer)) != EOF) {
        if (character == '\n') {
            if (current_length < min_length)
                min_length = current_length;
            current_length = 0;
            continue;
        }
        ++current_length;
    }
    return min_length;
}

int max_line_length_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    int max_length = 0, current_length = 0, character;
    while ((character = fgetc(file_pointer)) != EOF) {
        if (character == '\n') {
            if (current_length > max_length)
                max_length = current_length;
            current_length = 0;
            continue;
        }
        ++current_length;
    }
    return max_length;
}

int amount_of_lines_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    int amount = 0, character;
    while ((character = fgetc(file_pointer)) != EOF) {
        if (character == '\n')
            ++amount;
    }
    return amount;
}

void file_to_array_of_strings(FILE* file_pointer, char* array_of_lines, size_t max_line_len)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
    }

    rewind(file_pointer);

    char* buffer_pointer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;

    size_t i = 0;
    while ((line_length = getline(&buffer_pointer, &buffer_size, file_pointer)) != -1) {
        strcpy(array_of_lines + i * max_line_len, buffer_pointer);
        ++i;
    }
}
