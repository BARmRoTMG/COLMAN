#include "exam.h"

void rotate_right(int arr[], int size, int k)
{
	// מקרה קצה – מערך ריק או גודל לא חוקי
	if (size <= 0)
		return;   

	k = k % size; // נרמול k לטווח 0..size-1
	if (k < 0)
		k += size; // אם k שלילי – מתקן לסיבוב שמאלה
	if (k == 0)
		return;   // אין שינוי נדרש

	int* tmp = (int*)malloc(size * sizeof(int));
	if (!tmp)
		return;   // כשל בהקצאת זיכרון

	// מעתיקים כל איבר למיקום החדש אחרי הסיבוב
	for (int i = 0; i < size; i++)
	{
		int newIndex = (i + k) % size;
		tmp[newIndex] = arr[i];
	}

	// מחזירים את הערכים מהמערך הזמני למערך המקורי
	for (int i = 0; i < size; i++)
	{
		arr[i] = tmp[i];
	}

	// שחרור זיכרון זמני
	free(tmp); 
}
