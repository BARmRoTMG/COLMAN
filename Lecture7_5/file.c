#include <stdio.h>
#define SIZE 10

int main()
{
	int mul[SIZE];

	for (int i = 1; i < SIZE; i++)
	{
		mul[i - 1] = i * 5;
		printf("%d\t", mul[i - 1]);
	}


	return 0;
}