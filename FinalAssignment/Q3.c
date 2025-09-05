#include "exam.h"

int areAnagrams(const char* str1, const char* str2)
{
    if (!str1 || !str2) return 0;

    // אם האורכים שונים – אי אפשר להיות אנגרמה
    int len1 = (int)strlen(str1);
    int len2 = (int)strlen(str2);
    if (len1 != len2) return 0;

    // טבלת תדירויות לכל תו (ASCII)
    int freq[256] = { 0 };

    // סופרים מהראשונה, מחסרים מהשנייה
    for (int i = 0; i < len1; ++i)
    {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];
        ++freq[c1];
        --freq[c2];
    }

    // בודקים שהכול התאפס
    for (int i = 0; i < 256; ++i)
    {
        if (freq[i] != 0) return 0;
    }
    return 1;
}
