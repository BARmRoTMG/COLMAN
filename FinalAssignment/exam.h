#ifndef EXAM_H
#define EXAM_H

#define _CRT_SECURE_NO_WARNINGS
#define NULL 0

#define COLS 5  

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void fx1();

typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct
{
	char* startTrip;
	char* endTrip;
	Date dateTrip;
	int costTrip;
}Trip;

typedef struct
{
	char *fullName;
	char ID[10];
	char *email;
	char cellPhone[11];
	Trip** trips;
	int numTrips;
}Customer;

typedef struct
{
	Customer ** customers;
	int numCustomers;
}MoovitDB;

/* Q1 */
int* weightedEvenColumnSums(int matrix[][COLS], int rows);
/* Q2 */
void rotate_right(int arr[], int size, int k);
/* Q3 */
int areAnagrams(const char *str1, const char *str2);
/* Q4 */
char* removeDuplicates(const char *str);
/* Q5 */
char* sortByFrequency(const char *str);
/* Q6 */
int binary_as_number(int n);
/* Q7 */
int isAscendingDigits(int n);
/* Q8 */
Trip** getMostExpensiveTrips(const MoovitDB *db);
/* Q9 */
int addTripPointerToCustomer(Customer *cust, Trip *newTrip);
/* Q10 */
char* findTopVisitorToDestination(MoovitDB *db, char *destination);

#endif