#include "utf8_string_tools.h"
#include <stddef.h>
#include <string.h>

char* string_reverse(char* string)
{
    // char string[] = "Mình nói tiếng Việt HelloПриветэ!";

    if (!string || !*string)
        return string;

    for (size_t pos_left = 0, pos_right = strlen(string) - 1;
         pos_left < pos_right; pos_left++, pos_right--) {

        char ch = string[pos_left];
        string[pos_left] = string[pos_right];
        string[pos_right] = ch;
    }

    for (size_t pos_left = 0, char_continuation_size = 0; pos_left < strlen(string); pos_left++) {
        if (utf8_is_continuation(string[pos_left])) {
            ++char_continuation_size;
            continue;
        }
        for (size_t shift = char_continuation_size; shift > char_continuation_size / 2; shift--) {
            char tmp_byte = string[pos_left - (char_continuation_size - shift)];
            string[pos_left - (char_continuation_size - shift)] = string[pos_left - shift];
            string[pos_left - shift] = tmp_byte;
        }
        char_continuation_size = 0;
    }
    return string;
}

int utf8_is_continuation(char ch)
{
    return (ch & 0xc0) == 0x80;
}

int utf8_charsize(char* ch)
{
    size_t size = 0;
    do {
        ++size;
        ++ch;
    } while (utf8_is_continuation(*ch));
    return size;
}

size_t utf8_strlen(char* str)
{
    size_t i = 0, len = 0;
    while (str[i]) {
        if (!utf8_is_continuation(str[i]))
            ++len;
        ++i;
    }
    return len;
}
