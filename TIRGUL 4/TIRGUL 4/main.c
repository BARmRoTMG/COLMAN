#include "util.h"

int main()
{
	int num = 51234, index = 3;
	int digit = IndexOf(num, index);

	printf("The digit of the number %d in index %d is %d", num, index, digit);

	return 0;
}