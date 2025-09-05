#include "exam.h"

int count1 = 0;

void fx1()
{
	count1++;
}

void TestQ1(int m[][COLS], int rows, const int expected[], int n)
{
	int ok = 1;
	int* got = weightedEvenColumnSums(m, rows);

	if (!got)
	{
		ok = 0;
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			if (got[i] != expected[i])
			{
				ok = 0;
				break;
			}
		}
	}

	if (!ok)
		printf("your weightedEvenColumnSums( matrix, %d ) function is wrong (-2)\n", rows);

	if (got) free(got);
}

/* פונקציה להשוואת מערכים */
int arrays_equal(int* a, int* b, int n)
{
	for (int i = 0; i < n; i++)
		if (a[i] != b[i]) return 0;
	return 1;
}

/* פונקציית בדיקה ל-Q2 */
void TestQ2(int in[], int size, int k, int expected[], int n)
{
	int arr[100];  // נשתמש בהעתק כדי לא להרוס את המקור
	for (int i = 0; i < size; i++) arr[i] = in[i];

	rotate_right(arr, size, k);

	if (!arrays_equal(arr, expected, n))
	{
		printf("your rotate_right(arr, %d, %d) function is wrong (-2)\n", size, k);
	}
}

int main()
{
	printf("Test Start\n");

#pragma region Q1

	/*---------------------------Q1---------------------------*/
	printf("\nQ1 - weightedEvenColumnSums\n");

	/* 1) דוגמת המטלה */
	int m1[3][COLS] = {
		{2,7,3,4,1},
		{5,6,8,2,9},
		{1,3,2,5,4}
	};
	int exp1[3] = { 42, 198, 35 };
	TestQ1(m1, 3, exp1, 3);

	/* 2) שורה אחת בלבד */
	int m2[1][COLS] = { {10, 9, 8, 7, 6} };
	int exp2[1] = { 240 }; /* (10+8+6)*10 */
	TestQ1(m2, 1, exp2, 1);

	/* 3) ערכים שליליים */
	int m3[2][COLS] = {
		{-2,-7,-3,-4,-1},  /* even=-6, max=-1 => 6 */
		{-5,-6,-8,-2,-9}   /* even=-22, max=-2 => 44 */
	};
	int exp3[2] = { 6, 44 };
	TestQ1(m3, 2, exp3, 2);

	/* 4) אפסים בלבד */
	int m4[1][COLS] = { {0,0,0,0,0} };
	int exp4[1] = { 0 };
	TestQ1(m4, 1, exp4, 1);

	/* 5) מקסימום בעמודה זוגית */
	int m5[1][COLS] = { {5,1,9,0,2} };
	int exp5[1] = { 144 }; /* even=16, max=9 */
	TestQ1(m5, 1, exp5, 1);

	/* 6) מקסימום בעמודה אי-זוגית */
	int m6[1][COLS] = { {3,8,7,6,5} };
	int exp6[1] = { 120 }; /* even=15, max=8 */
	TestQ1(m6, 1, exp6, 1);

	/* 7) מקסימום מופיע כמה פעמים */
	int m7[1][COLS] = { {4,9,4,1,9} };
	int exp7[1] = { 153 }; /* even=17, max=9 */
	TestQ1(m7, 1, exp7, 1);

	/* 8) שורות עם תוצאה 0 בשורה אחת, ו־5 בשורה שנייה */
	int m8[2][COLS] = {
		{0,1,0,1,0}, /* even sum=0, max=1 => 0 */
		{0,0,0,5,1}  /* even sum=0+0+1=1, max=5 => 5 */
	};
	int exp8[2] = { 0, 5 };
	TestQ1(m8, 2, exp8, 2);

	/* 9) סכום קטן, מקסימום גדול */
	int m9[1][COLS] = { {1,100,1,100,1} };
	int exp9[1] = { 300 }; /* even sum=3, max=100 */
	TestQ1(m9, 1, exp9, 1);

	/* 10) סכום גדול, מקסימום קטן */
	int m10[1][COLS] = { {5,1,5,1,5} };
	int exp10[1] = { 75 }; /* even sum=15, max=5 */
	TestQ1(m10, 1, exp10, 1);
#pragma endregion

#pragma region Q2
	/*---------------------------Q2---------------------------*/

	printf("\nQ2 - rotate_right\n");

	/* 1) דוגמה מהמטלה */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 4,1,2,3 };
		TestQ2(a, 4, 1, e, 4);
	}

	/* 2) k=0 (אין שינוי) */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 1,2,3,4 };
		TestQ2(a, 4, 0, e, 4);
	}

	/* 3) k=size (גם אין שינוי) */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 1,2,3,4 };
		TestQ2(a, 4, 4, e, 4);
	}

	/* 4) k>size (בדוק מודולו) */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 3,4,1,2 }; // k=6 -> כמו k=2
		TestQ2(a, 4, 6, e, 4);
	}

	/* 5) מערך בגודל 1 */
	{
		int a[1] = { 7 };
		int e[1] = { 7 };
		TestQ2(a, 1, 5, e, 1);
	}

	/* 6) מערך בגודל 2 */
	{
		int a[2] = { 9,8 };
		int e[2] = { 8,9 };
		TestQ2(a, 2, 1, e, 2);
	}

	/* 7) מספר שלילי ברוטציה */
	{
		int a[5] = { 10,20,30,40,50 };
		int e[5] = { 20,30,40,50,10 }; // k=-1 -> סיבוב שמאלה אחד
		TestQ2(a, 5, -1, e, 5);
	}

	/* 8) ערכים שליליים במערך */
	{
		int a[5] = { -1,-2,-3,-4,-5 };
		int e[5] = { -2,-3,-4,-5,-1 }; // k=4 -> כמו k=-1
		TestQ2(a, 5, 4, e, 5);
	}

	/* 9) k=2 בגודל 5 */
	{
		int a[5] = { 1,2,3,4,5 };
		int e[5] = { 4,5,1,2,3 };
		TestQ2(a, 5, 2, e, 5);
	}

	/* 10) מערך עם חזרות — k=4 (שקול לשמאלה 2) */
	{
		int a[6] = { 1,1,2,2,3,3 };
		int e[6] = { 2,2,3,3,1,1 };  // תיקון כאן
		TestQ2(a, 6, 4, e, 6);
	}

#pragma endregion



	printf("\n\ndone\n");
	return 0;
}