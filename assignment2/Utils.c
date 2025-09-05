/*---------------------------Mavo - EX2--------------------------*/
// Prepared by: Bar Mashiach
//              315111849
//              09/06/2025
/*---------------------------------------------------------------------*/

#include "Utils.h"

//-----------------------------------------------------------------------------------------------//
//Q1
int RemoveDuplicates(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		// We check each number with the one after it.
		for (int j = i + 1; j < size;)
		{
			// Move all the the numbers from the right of j to the left.
			if (arr[i] == arr[j])
			{
				for (int k = j; k < size - 1; k++)
					arr[k] = arr[k + 1];

				// Removing the duplicates by decreasing the array.
				size--;
			}
			else
			{
				// Advance if there are no duplicates.
				j++;
			}
		}
	}
	return size;
}
//-----------------------------------------------------------------------------------------------//
//Q2
void InsertionSort(int arr[], int size)
{
	// Start from 1 so we could compare with the element before it.
	for (int i = 1; i < size; i++)
	{
		int temp = arr[i];
		// Keep track of what value I'm comparing the left of i.
		int j = i - 1;

		while (j >= 0 && arr[j] > temp)
		{
			// Move element to the right
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}
//-----------------------------------------------------------------------------------------------//
//Q3
void FlipMatrix(int mat[MATRIX_SIZE][MATRIX_SIZE], int option)
{
	int i, j;
	int tempM[MATRIX_SIZE][MATRIX_SIZE];

	switch (option)
	{
	case 1:
		// 90 Right 
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			for (j = 0; j < MATRIX_SIZE; j++)
			{
				tempM[j][MATRIX_SIZE - 1 - i] = mat[i][j];
			}
		}
		break;

	case 2:
		// 90 Left
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			for (j = 0; j < MATRIX_SIZE; j++)
			{
				tempM[MATRIX_SIZE - 1 - j][i] = mat[i][j];
			}
		}
		break;

	case 3:
		// Top to bottom
		for (i = 0; i < MATRIX_SIZE / 2; i++)
		{
			for (j = 0; j < MATRIX_SIZE; j++)
			{
				int temp = mat[i][j];
				mat[i][j] = mat[MATRIX_SIZE - 1 - i][j];
				mat[MATRIX_SIZE - 1 - i][j] = temp;
			}
		}
		return; // already in place

	case 4:
		// Left to right
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			for (j = 0; j < MATRIX_SIZE / 2; j++)
			{
				int temp = mat[i][j];
				mat[i][j] = mat[i][MATRIX_SIZE - 1 - j];
				mat[i][MATRIX_SIZE - 1 - j] = temp;
			}
		}
		return; //already inplace
	}

	// Copy result back to original matrix (for rotations)
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			mat[i][j] = tempM[i][j];
		}
	}
}

//-----------------------------------------------------------------------------------------------//
//Q4
int CountSemiSimilar(char a[][M], char b[][M], int n)
{
	int count = 0;

	for (int i = 0; i < n; i++)
	{
		int lenA = strlen(a[i]);
		int lenB = strlen(b[i]);

		if (lenA != lenB)
			continue;

		int aSorted[M], bSorted[M];

		// Convert chars to ints
		for (int j = 0; j < lenA; j++)
		{
			aSorted[j] = (int)a[i][j];
			bSorted[j] = (int)b[i][j];
		}

		InsertionSort(aSorted, lenA);
		InsertionSort(bSorted, lenA); // same length

		// Compare sorted arrays
		int isSame = 1;
		for (int j = 0; j < lenA; j++)
		{
			if (aSorted[j] != bSorted[j])
			{
				isSame = 0;
				break;
			}
		}

		if (isSame)
			count++;
	}

	return count;
}


//-----------------------------------------------------------------------------------------------//