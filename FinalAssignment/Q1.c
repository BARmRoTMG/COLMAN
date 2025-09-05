#include "exam.h"

int* weightedEvenColumnSums(int matrix[][COLS], int rows) 
{
	if (rows <= 0) return NULL;

	int* res = (int*)malloc(rows * sizeof(int));
	if (!res) return NULL;

	//שורות 
	for (int i = 0; i < rows; i++)
	{
		int max = matrix[i][0];
		int evenSum = 0;

		//עמודות
		for (int j = 0; j < COLS; j++)
		{
			int temp = matrix[i][j];

			if (temp > max)
				max = temp;

			if (j % 2 == 0)
				evenSum += temp;
		}
		res[i] = evenSum * max;
	}
	return res;
}
