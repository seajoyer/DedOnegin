#include <stddef.h>

int utf8_is_continuation(char ch)
{
    return (ch & 0xc0) == 0x80;
}

int utf8_charsize(char* ch) {
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
