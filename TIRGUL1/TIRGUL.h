#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define PI 3.14

//EX 2
//int main()
//{
//	int num1,num2;
//	int sum, diff, mult;
//
//	printf("enter two numbers: \n");
//	scanf("%d%d", &num1, &num2);
//
//	sum = num1 + num2;
//	diff = num1 - num2;
//	mult = num1 * num2;
//
//	printf("the sum of the numbers is: %d\n", sum);
//	printf("the difference between the numbers is: %d\n", diff);
//	printf("the multiplication of the numbers is: %d\n", mult);
//
//	return 0;
//}

//EX 3
//int main()
//{
//	int rad;
//	float area, perimeter;
//
//	printf("Enter the circle's radius: ");
//	scanf("%d", &rad);
//
//	perimeter = 2 * PI * rad;
//	area = PI * pow(rad, 2);
//
//	printf("The perimeter of the circle is: %f\n", perimeter);
//	printf("The area of the circle is: %f", area);
//	return 0;
//}

//EX 5
//int main()
//{
//	int x1, x2, y1, y2;
//	float perimeter, area;
//	float l1, l2, l3;
//
//	printf("Enter cordinations #1 (X,Y) : \n");
//	scanf("%d%d", &x1, &y1);
//
//	printf("Enter cordinations #2 (X,Y) : \n");
//	scanf("%d%d", &x2, &y2);
//
//	l1 = sqrt(pow(x1, 2) + pow(y1, 2));
//	l2 = sqrt(pow(x2, 2) + pow(y2, 2));
//	l3 = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
//	area = (l1 * l2) / 2;
//	perimeter = l1 + l2 + l3;
//
//	printf("area: %f\n", area);
//	printf("perimeter: %f\n", perimeter);
//
//	return 0;
//}

//EX 6
//int main()
//{
//	int x, y;
//	int sum, diff, prod, remainder;
//	float quot;
//
//	printf("Please enter two numbers: ");
//	scanf("%d%d", &x, &y);
//
//	sum = x + y;
//	diff = abs(x - y);
//	prod = x * y;
//	quot = float(x / y);
//	remainder = x % y;
//
//	printf("Sum: %d\nDifference: %d\nProduct: %d\nQuotient: %f\nRemainder: %d", sum, diff, prod, quot, remainder);
//
//	return 0;
//}

int main() {
	int n1, n2, n3, sum, mul;
	float avg;

	printf("Please enter 3 numbers: \n");
	scanf("%d%d%d", &n1, &n2, &n3);

	n1++;
	n2++;
	n3++;

	sum = n1 + n2 + n3;
	mul = n1 * n2 * n3;
	avg = (float)sum / 3.0;

	printf("Sum: %d\nMulti: %d\nAvarage: %f", sum, mul, avg);

	return 0;
}