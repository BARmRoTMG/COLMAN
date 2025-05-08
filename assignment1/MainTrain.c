/*---------------------------Ex 3 - MainTrain--------------------------*/
// Prepared by: Aviv Shukrun
/*---------------------------------------------------------------------*/

#include <stdio.h>
#include "Util.h"

void Test1(int num, int result)
{
	if (NumOfDigits(num) != result)
		printf("your NumOfDigits( %d ) function is wrong (-2)\n", num);
}

void Test2(int wage, int extraWage, float extraHours, int numOfDeals, float result)
{
	if (CalculateSalary(wage, extraWage, extraHours, numOfDeals) != result)
		printf("your CalculateSalary( %d, %d, %.2f, %d ) function is wrong (-2)\n", wage, extraWage, extraHours, numOfDeals);
}

void Test3(int numOfProducts, float productPrice, int productType, float result)
{
	if (CarPartsPrice(numOfProducts, productPrice, productType) != result)
		printf("your CarPartsPrice( %d, %.2f, %d ) function is wrong (-2)\n", numOfProducts, productPrice, productType);
}

void Test4(int num, int result)
{
	if (OddNumber(num) != result)
		printf("your OddNumber( %d ) function is wrong (-2)\n", num);
}

void	Test5(int num, int result)
{
	if (SumOfDigits(num) != result)
		printf("your SumOfDigits( %d ) function is wrong (-2)\n", num);
}

void Test6(int num1, int num2, int result)
{
	if (Contains(num1, num2) != result)
		printf("your Contains( %d, %d ) function is wrong (-2)\n", num1, num2);
}

void main()
{
	int points = 0;
	printf("Test Start\n");
	/*---------------------------Part A---------------------------*/
	printf("\nPart A - NumOfDigits\n");
	Test1(-15, -1);
	Test1(0, 1);
	Test1(100, 3);
	Test1(55555, 4);

	/*---------------------------Part B---------------------------*/
	printf("\nPart B - CalculateSalary\n");
	Test2(8000, 50, 7, 10, 10750);
	Test2(3000, 40, 7, 2, 3280);
	Test2(4000, 40, 6, 6, 4440);
	Test2(5000, 40, 12, 6, 5980);
	Test2(5000, 40, 3, 10, 6120);

	/*---------------------------Part C---------------------------*/
	printf("\nPart C - CarPartsPrice\n");
	Test3(80, 70, 4, 5320);
	Test3(80, 70, 6, 5320);
	Test3(35, 70, 4, 2450);
	Test3(34, 70, 4, 2380);
	Test3(40, 30, 7, 960);

	/*---------------------------Part D---------------------------*/
	printf("\nPart D - OddNumber\n");
	Test4(12345, 135);
	Test4(4, 0);
	Test4(12, 1);
	Test4(123456, 135);
	Test4(999, 999);

	/*---------------------------Part E---------------------------*/
	printf("\nPart E - SumOfDigits\n");
	Test5(-5, -1);
	Test5(19, 1);
	Test5(654987, 3);
	Test5(1009, 1);

	/*---------------------------Part F---------------------------*/
	printf("\nPart F - Contains\n");
	Test6(693, 693, 2);
	Test6(693, 69, 2);
	Test6(693, 1693, -1);
	Test6(4, 4, 0);
	Test6(4589439, 45, 6);

	/*---------------------------Finish---------------------------*/
	printf("\n\ndone\n");
}