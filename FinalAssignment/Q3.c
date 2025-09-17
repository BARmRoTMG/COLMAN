#include "exam.h"

int areAnagrams(const char* str1, const char* str2)
{
    // מקרה קצה
    if (!str1 || !str2)
        return 0;

    // טבלת תדירויות לכל תו (ASCII)
    int* frequency = (int*)calloc(256, sizeof(int));

    if (frequency == NULL) return 0;

    // מעבר סימולטני: סופרים מהראשונה ומחסרים מהשנייה
    // אם אחת נגמרת לפני השנייה – האורכים שונים = לא אנגרמה
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        // בדיקה שאחת המחרוזות לא נגמרה מוקדם
        if (str1[i] == '\0' || str2[i] == '\0')
        {
            free(frequency);
            return 0; // אורכים שונים
        }

        unsigned char ch1 = (unsigned char)str1[i];
        unsigned char ch2 = (unsigned char)str2[i];

        frequency[ch1]++; // הוספה לתו מהמחרוזת הראשונה
        frequency[ch2]--; // חיסור לתו מהמחרוזת השנייה

        i++;
    }


    // וידוא שכל המונים התאפסו
    for (int pos = 0; str1[pos] != '\0'; pos++)
    {
        unsigned char current_char = (unsigned char)str1[pos];
        if (frequency[current_char] != 0)
        {
            free(frequency);
            return 0;
        }
    }
    free(frequency);
    return 1;
}
