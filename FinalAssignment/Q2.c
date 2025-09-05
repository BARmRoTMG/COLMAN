#include "exam.h"

void rotate_right(int arr[], int size, int k)
{
    if (size <= 0) return;

    // נרמול k לטווח 0..size-1 (תומך גם ב-k שלילי וגם ב-k גדול)
    k = k % size;
    if (k < 0) k += size;
    if (k == 0) return;

    int* tmp = (int*)malloc(size * sizeof(int));
    if (!tmp) return;

    for (int i = 0; i < size; i++)
    {
        int newIndex = (i + k) % size;  // כעת newIndex תמיד לא-שלילי
        tmp[newIndex] = arr[i];
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = tmp[i];
    }
    free(tmp);
}
