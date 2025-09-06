#include "exam.h"

int areAnagrams(const char* str1, const char* str2)
{
    // מקרה קצה – אחד המצביעים NULL
    if (!str1 || !str2)
        return 0;

    // טבלת תדירויות לכל תו (ASCII)
    int freq[256] = { 0 };

    // מעבר סימולטני: סופרים מהראשונה ומחסרים מהשנייה
    // אם אחת נגמרת לפני השנייה – האורכים שונים => לא אנגרמה
    int i = 0;
    while (1)
    {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];

        // אם שתי המחרוזות נגמרו יחד – יוצאים מהלולאה
        if (c1 == '\0' && c2 == '\0')
            break;

        // אם אחת נגמרה לפני השנייה – אורכים שונים
        if (c1 == '\0' || c2 == '\0')
            return 0;

        // עדכון התדירויות
        ++freq[c1];
        --freq[c2];

        ++i;
    }

    // בדיקה שכל התדירויות התאפסו
    for (int k = 0; k < 256; ++k)
    {
        if (freq[k] != 0)
            return 0;
    }
    return 1;
}
