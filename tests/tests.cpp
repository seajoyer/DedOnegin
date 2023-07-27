#include "file_parser.h"
#include "lexicographic_sort.h"
#include "quick_sort.h"
#include <cstring>
#include <cwchar>
#include <gtest/gtest.h>
#include <stddef.h>
#include <stdio.h>

#define SOURCE_FILE "Eugene-Onegin.txt"
#define RESULT_FILE "out.txt"
#define MAX_LINE_LEN 35

TEST(OpenFile, src)
{
    FILE* src_file = fopen("Eugene-Onegin.txt", "r");

    ASSERT_NE(nullptr, src_file);

    fclose(src_file);
}

TEST(OpenFile, out)
{
    FILE* out_file = fopen(RESULT_FILE, "r");

    ASSERT_TRUE(out_file != nullptr);

    fclose(out_file);
}

TEST(ParseFile, number_lines)
{
    FILE* src_file = fopen(SOURCE_FILE, "r");

    wint_t wc = L'\0';
    size_t number_lines = 0;
    while((wc = fgetwc(src_file)) != WEOF)
        if (wc == L'\n')
            ++number_lines;

    rewind(src_file);

    arrayLines array_lines = readToLines(src_file);

    ASSERT_EQ(number_lines, array_lines.size);

    fclose(src_file);
}

void linesPreprocess(line* p_l1, line* p_l2, const wchar_t* ws1, const wchar_t* ws2)
{
    memset((*p_l1).content, L'\0', MAX_LINE_LEN);
    memset((*p_l2).content, L'\0', MAX_LINE_LEN);

    wcscpy((*p_l1).content, ws1);
    wcscpy((*p_l2).content, ws2);

    size_t len1 = 0;
    for (size_t i = 0; (*p_l1).content[i] != L'\0'; i++)
        ++len1;

    size_t len2 = 0;
    for (size_t i = 0; (*p_l2).content[i] != L'\0'; i++)
        ++len2;

    *p_l1 = { (*p_l1).content, len1 };
    *p_l2 = { (*p_l2).content, len2 };
}

TEST(CompareLines, forward)
{
    line l1 = { (wchar_t* const)calloc(MAX_LINE_LEN, sizeof(wchar_t)), 0 };
    line l2 = { (wchar_t* const)calloc(MAX_LINE_LEN, sizeof(wchar_t)), 0 };

    linesPreprocess(&l1, &l2, L"ab", L"ac");
    EXPECT_LT(compareLexicographically(l1, l2, +1), 0);

    linesPreprocess(&l1, &l2, L"эюя", L"яюэ");
    EXPECT_LT(compareLexicographically(l1, l2, +1), 0);

    linesPreprocess(&l1, &l2, L"Hello, Arcturus!", L"Hello, Antares!");
    EXPECT_GT(compareLexicographically(l1, l2, +1), 0);

    linesPreprocess(&l1, &l2, L"Привет, Арктур!", L"Привет, Антарес!");
    EXPECT_GT(compareLexicographically(l1, l2, +1), 0);

    linesPreprocess(&l1, &l2, L"\0", L"\0");
    EXPECT_EQ(compareLexicographically(l1, l2, +1), 0);

    linesPreprocess(&l1, &l2, L"Hello, World", L"Hello, World");
    EXPECT_EQ(compareLexicographically(l1, l2, +1), 0);

    free(l1.content);
    free(l2.content);
}

TEST(CompareLines, backward)
{
    line l1 = { (wchar_t* const)calloc(MAX_LINE_LEN, sizeof(wchar_t)), 0 };
    line l2 = { (wchar_t* const)calloc(MAX_LINE_LEN, sizeof(wchar_t)), 0 };

    linesPreprocess(&l1, &l2, L"ab", L"ac");
    EXPECT_LT(compareLexicographically(l1, l2, -1), 0);

    linesPreprocess(&l1, &l2, L"эюя", L"яюэ");
    EXPECT_GT(compareLexicographically(l1, l2, -1), 0);

    linesPreprocess(&l1, &l2, L"Hello, World!  = *-", L"Hello, World!-* =  ");
    EXPECT_EQ(compareLexicographically(l1, l2, -1), 0);

    linesPreprocess(&l1, &l2, L"Hello, Arcturus!", L"Hello, Antares!");
    EXPECT_GT(compareLexicographically(l1, l2, -1), 0);

    linesPreprocess(&l1, &l2, L"Привет, Арктур! .", L"Привет, Антарес!");
    EXPECT_LT(compareLexicographically(l1, l2, -1), 0);

    linesPreprocess(&l1, &l2, L"\0", L"\0");
    EXPECT_EQ(compareLexicographically(l1, l2, -1), 0);

    free(l1.content);
    free(l2.content);
}

int compare(const void* ch1, const void* ch2) { return(tolower(*(const char*)ch1) - tolower(*(const char*)ch2)); }

TEST(Sortings, quick_sort)
{
    char arr[] = "DBgFaec";

    quick_sort(arr, 7, sizeof(char), compare);

    ASSERT_EQ(strcmp(arr, "aBcDeFg"), 0);
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    ::testing::InitGoogleTest();
  
    return RUN_ALL_TESTS();
}
