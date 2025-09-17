#include "exam.h"

int binary_as_number(int n) {

	/******** DON'T CHANGE ********/
	fx1(); // do not change!!!
	/******************************/
	
	/*Write your code down here*/
	if (n == 0) return 0;
	if (n == 1) return 1;

	// בכל קריאה מחלק את המספר בחצי כדי להתקדם לביט הבא, מכפיל ב10 כדי לפנות מקום לספרה החדשה ומוסיף את הביט הימני 
	return binary_as_number(n / 2) * 10 + (n % 2);
}
