#include "Util.h"

int main()
{
	int arr[SIZE_10], sum;

	init(arr, SIZE_10);
	print(arr, SIZE_10);
	sum = sumEvenNumbers(arr, SIZE_10);
	printf("Sum of even numbers is: %d", sum);
	shiftLeftArr(arr, SIZE_10);

	return 0;
}