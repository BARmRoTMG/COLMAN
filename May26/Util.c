#include "Util.h"

void check(int* numbers, int size, int min, int max, int* p_smaller, int* p_bigger) 
{
	int* temp = numbers;
	*p_smaller = 0;
	*p_bigger = 0;

	for (int i = 0; i < size; i++)
	{
		if (*temp < min)
			(* p_smaller)++;

		if (*temp > max)
			(* p_bigger)++;

		temp++;
	}
}