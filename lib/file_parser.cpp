/*!
 * \file
 * Useful functions to parse files
 */
#include "file_parser.h"
#include <assert.h>
#include <limits.h>
#include <string.h>

/*!
 * \param[in] file_pointer
 * \return The number of the shortest string in the file
 */
size_t shortest_string_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    char character;
    size_t min_length = ULONG_MAX, min_line_index = 1;
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

/*!
 * \param[in] file_pointer
 * \return The number of the longest string in the file
 */
size_t longest_string_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return -1;
    }

    rewind(file_pointer);

    char character;
    size_t max_length = 0, max_string_index = 1;
    for (size_t i = 0, current_string_index = 0; (character = fgetc(file_pointer)) != EOF; i++) {
        if (character == '\n') {
            if (i > max_length) {
                max_length = i;
                max_string_index = current_string_index;
            }
            i = 0;
            ++current_string_index;
        }
    }
    return max_string_index;
}

/*!
 * \param[in] file_pointer
 * \return The length of the shortest string in a file
 */
size_t min_string_length_in_file(FILE* file_pointer)
{
    if (file_pointer == NULL) {
        printf("Could't read the file!");
        return 0;
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

/*!
 * \param[in] file_pointer
 * \return The length of the longest string in a file
 */
size_t get_max_line_len(FILE* file_pointer)
{
    assert(file_pointer && "Could't read the file!");

    rewind(file_pointer); // TODO: save the cursor position

    int max_length = 0, current_length = 0, character = '\0';
    while ((character = fgetc(file_pointer)) != EOF) {
        ++current_length;
        if (character == '\n') {
            if (current_length > max_length)
                max_length = current_length; // TODO: use macro to find the max value!
            current_length = 0;
            continue;
        }
    }
    return max_length;
}

/*!
 * \param[in] file_pointer
 * \return The amount of strings in the file
 */
size_t get_line_count(FILE* file_pointer)
{
    if (!file_pointer) {
        printf("Could't read the file!");
        return 0;
    }

    rewind(file_pointer);

    int amount = 0, character = '\0';
    while ((character = fgetc(file_pointer)) != EOF) {
        if (character == '\n')
            ++amount;
    }
    return amount;
}

/*!
 * Convert the file's content to the array of strings
 * \param[in] file_pointer
 * \param[in] max_string_len The length of the longest string in the file
 * \param[out] array_of_strings
 */
void file_to_array_of_strings(FILE* file_pointer, char* array_of_strings, size_t max_string_len)
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
        strcpy(array_of_strings + i * max_string_len, buffer_pointer);
        ++i;
    }
}
