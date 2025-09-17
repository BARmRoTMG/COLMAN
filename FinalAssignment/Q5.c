#include "exam.h"

#define ASCII 256

char* sortByFrequency(const char *str) {
    if (!str) return NULL;

    int len = (int)strlen(str);

    // הקצאה דינמית למחרוזת החדשה
    char* result = malloc(len + 1);
    if (!result) return NULL;  // בדיקת הקצאה

    // מערך לסימון תווים שכבר עובדנו עליהם
    int used[ASCII] = { 0 };
    int pos = 0;

    // עיבור על המחרוזת כמה פעמים - מ-len עד 1
    for (int f = len; f > 0; f--)
    {
        for (int i = 0; i < len; i++)
        {
            char ch = str[i];
            if (!used[(unsigned char)ch])
            {
                int count = 0;
                for (int k = 0; k < len; k++)
                {
                    if (str[k] == ch) count++;
                }
                if (count == f)
                {
                    for (int j = 0; j < f; j++)
                    {
                        result[pos] = ch;
                        pos++;
                    }
                    used[(unsigned char)ch] = 1;
                }
            }
        }
    }

    result[pos] = '\0';
    return result;
}