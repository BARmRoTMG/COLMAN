#include "Util.h"

void init(int arr[], int size)
{
	printf("Please enter %d numbers:\n", size);

	for (int i = 0; i < size; ++i)
	{
		scanf_s("%d", &arr[i]);
	}
}

void print(int arr[], int size)
{
	printf("Here are your numbers: \n");
	for (int i = 0; i < size; i++)
	{
		printf("%d \t", arr[i]);
	}
}

int sumEvenNumbers(int arr[], int size)
{
	int sum = 0;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
			sum += arr[i];
	}

	return sum;
}

void shiftLeftArr(int arr[], int size)
{

}