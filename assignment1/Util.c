/*---------------------------Mavo - EX1--------------------------*/
// Prepared by: Bar Mashiach
//              315111849
//              The program handles logic for different given cases.
/*---------------------------------------------------------------------*/

#include "Util.h"

//Conditions
int NumOfDigits(int num)
{
	// Checks for negative numbers
	if (num < 0)
		return -1;

	// Checks if the number has single digit.
	if (num >= 0 && num <= 9)
		return 1;

	// Checks if the number has double digits.
	if (num < 100)
		return 2;

	// Checks if the number has 3 digits.
	if (num < 1000)
		return 3;

	// If no term is met, the func will return 4.
	return 4;
}

// Conditions
float CalculateSalary(int wage, int extraWage, float extraHours, int numOfDeals)
{
	// floats to help with calculations.
	float extraSalary = extraWage * extraHours;
	float bonusPercent = 0.0f;

	// Were there any deals made?
	if (numOfDeals <= 0)
		return -1;

	// 1–4 deals plus overtime
	if (numOfDeals <= 4)
		return wage + extraSalary;

	// 5–7 deals plus 5/10% and overtime.
	if (numOfDeals >= 5 && numOfDeals <= 7)
	{
		// Extra hours less then 10 or over. adds bonus accordinly.
		if (extraHours < 10)
			return wage * 1.05f + extraSalary; // 5% bonus
		else
			return wage * 1.10f + extraSalary; // 10% bonus
	}

	// More than 7 deals, gets bonus percent on number of deals based on extra hours.
	// We don't need to check the num of deals because if we get here then all other terms aren't met therefore this must be the case.
	if (extraHours < 5)
		bonusPercent = numOfDeals * 2;
	else
		bonusPercent = numOfDeals * 3;

	// Bonus calculation
	float bonus = wage * (bonusPercent / 100.0f);
	return wage + bonus + extraSalary;
}

// Switch Case
float CarPartsPrice(int numOfProducts, float productPrice, int productType)
{
	// We check if the purchase containts more then 35 products.
	if (numOfProducts > 35)
	{
		// Make cases based on product type to give specific discount.
		switch (productType)
		{
		case 1:
		case 4:
		case 6:
			return numOfProducts * productPrice * 0.95f;

		case 2:
		case 5:
			return numOfProducts * productPrice * 0.90f;

		case 3:
		case 7:
		case 8:
			return numOfProducts * productPrice * 0.80f;
		}
	}

	// Less then 35 products will result in no discount.
	return numOfProducts * productPrice;
}

//Loops
int OddNumber(int num)
{
	// Declaring ints and an array.
	int count = 0;
	int result = 0;
	int digits[20];

	// Checking if the number is 0 or negative.
	if (num == 0 || num < 0)
		return 0;

	while (num != 0)
	{
		// Saves last digit in array.
		digits[count] = num % 10;
		// Removes Last digit from num and adds one to our count.
		num /= 10;
		count++;
	}

	// Because we stored the numbers from num to the array backwords, we reverse them here while checking in only the odd numbers using modulu.
	for (int i = count - 1; i >= 0; i--)
	{
		if (digits[i] % 2 != 0)
		{
			result = result * 10 + digits[i];
		}
	}

	return result;
}

int SumOfDigits(int num)
{
	// Return -1 for negative numbers.
	if (num < 0)
		return -1;

	// Do this as long as our number is 2 digits.
	while (num >= 10)
	{
		int sum = 0;

		// Do this as long as our number is not 0
		while (num != 0)
		{
			// Add up the last digit of the given num to the sum, remove it.
			sum += num % 10;
			num /= 10;
		}
		// We get here when the number gets to 0 after summing all the digits together, and we go back to the bigger while loop if the sum is >= 10.
		num = sum;
	}

	return num;
}

int Contains(int num1, int num2)
{
	// מחשבים כמה ספרות יש ב־num2
	int len2 = 0;
	int temp = num2;
	while (temp > 0)
	{
		len2++;
		temp /= 10;
	}

	for (int i = 0; num1 > 0; i++)
	{
		int temp1 = num1;
		int temp2 = num2;
		int match = 1;

		while (temp2 > 0)
		{
			if (temp1 == 0 && temp2 > 0)
			{
				match = 0;
				break;
			}

			if (temp1 % 10 != temp2 % 10)
			{
				match = 0;
				break;
			}

			temp1 /= 10;
			temp2 /= 10;
		}

		if (match && temp2 == 0)
		{
			return i + len2 - 1;  // ← זה הפתרון!
		}

		num1 /= 10;
	}

	return -1;
}
