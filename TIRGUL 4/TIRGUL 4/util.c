#include "util.h"

int Length(int num)
{
	if (num == 0) return 1;

	int count = 0;

	while (num != 0) 
	{
		num /= 10;
		count++;
	}
	return count;
}

int IndexOf(int num, int index)
{
	int i;
	int len = Length(num);

	if (index < 0 || index >= len)
		return -1;

	for (i = 0; i < index; i++)
	{
		num /= 10;
	}

	return (num % 10);
}