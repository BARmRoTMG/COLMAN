#include "Util.h"

int NumOfDigits(int num)
{
	if (num < 0)
		return -1;

	if (num >= 0 && num <= 9)
		return 1;

	if (num < 100)
		return 2;

	if (num < 1000)
		return 3;

	return 4;
}

float CalculateSalary(int wage, int extraWage, float extraHours, int numOfDeals)
{
	float extraSalary = extraWage * extraHours;
	float bonusPercent = 0.0f;

	if (numOfDeals <= 0)
		return -1;

	if (numOfDeals <= 4)
		return wage + extraSalary;

	if (numOfDeals >= 5 && numOfDeals <= 7)
	{
		if (extraHours < 10)
			return (wage * 1.05f) + extraSalary;

		if (numOfDeals >= 10)
			return (wage * 1.10f) + extraSalary;
	}

	if (numOfDeals > 7)
	{
		if (extraHours < 5)
			return 5;
		else if (extraHours >= 5)
			return 5;

	}
}

float CarPartsPrice(int numOfProducts, float productPrice, int productType)
{
	return 0;
}

int OddNumber(int num)
{
	return 0;
}

int SumOfDigits(int num)
{
	return 0;
}

int Contains(int num1, int num2)
{
	return 0;
}