#include "exam.h"

char* removeDuplicates(const char *str) {
    // מקרה קצה
    if (!str)
        return NULL;

    // טבלת תדירות לכל תו (ASCII)
    int freq[256] = { 0 };

    // ספירת תדירויות וחישוב אורך
    int len = 0;
    while (str[len] != '\0')
    {
        unsigned char c = (unsigned char)str[len];
        ++freq[c];
        ++len;
    }

    // ספירת כמות התווים הייחודיים (שהופיעו פעם אחת)
    int keep = 0;
    for (int i = 0; i < len; ++i)
    {
        unsigned char c = (unsigned char)str[i];
        if (freq[c] == 1)
            ++keep;
    }

    // הקצאת מחרוזת פלט באורך מתאים + תו סיום
    char* out = (char*)malloc((keep + 1) * sizeof(char));
    if (!out)
        return NULL;

    // מילוי הפלט בתווים הייחודיים לפי סדר המקור
    int w = 0;
    for (int i = 0; i < len; ++i)
    {
        unsigned char c = (unsigned char)str[i];
        if (freq[c] == 1)
            out[w++] = (char)c;
    }

    // תו סיום
    out[w] = '\0';
    return out;
}
