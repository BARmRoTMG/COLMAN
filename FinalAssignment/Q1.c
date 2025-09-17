#include "exam.h"

int* weightedEvenColumnSums(int matrix[][COLS], int rows)
{
    // בדיקת מקרי קצה
    if (rows <= 0 || matrix == NULL)
        return NULL;

    // הקצאת זיכרון לתוצאות
    int* res = (int*)malloc(rows * sizeof(int));
    if (!res)
        return NULL;

    // לולאה על כל השורות במטריצה
    for (int i = 0; i < rows; ++i)
    {
        int maxVal = matrix[i][0]; // ערך התחלתי למקסימום
        int evenSum = 0; // סכום עמודות זוגיות

        // מעבר על כל העמודות בשורה i 
        for (int j = 0; j < COLS; ++j)
        {
            int val = matrix[i][j];

            // עדכון מקסימום אם נמצא ערך גדול יותר 
            if (val > maxVal)
                maxVal = val;

            // חיבור הערך אם העמודה זוגית
            if ((j & 1) == 0)
                evenSum += val;
        }

        // שמירת התוצאה במערך הפלט
        res[i] = evenSum * maxVal;
    }

    // החזרת המערך הדינאמי
    return res;
}