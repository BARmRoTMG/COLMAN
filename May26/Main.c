#include "Util.h"

int main()
{
	int arr[SIZE] = { -10, 5, -3, 7, 0, -8, 12, -1, 4, -6, 9, -2, 15, -4, 3, -7, 6, -9, 11, -5 };
	int min = 5;
	int max = 20;
	int smaller, bigger;

	check(arr, SIZE, min, max, &smaller, &bigger);

	printf("Numbers smaller than %d: %d\n", min, smaller);
	printf("Numbers greater than %d: %d\n", max, bigger);

	return 0;
}