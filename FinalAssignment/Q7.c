#include "exam.h"

int isAscendingDigits(int n)
{

	/******** DON'T CHANGE ********/
	fx1(); // do not change!!!
	/******************************/

	/*Write your code down here*/

	// מספר חד-ספרתי תמיד "עולה" טריוויאלית
	if (n < 10) return 10;

	int curr = n % 10;           // הספרה הימנית הנוכחית
	int prev = (n / 10) % 10;    // השכנה שמשמאלה (קודמת לה משמאל-לימין)

	// אם נשבר הסדר (prev >= curr) – מחזירים את הספרה השוברת (prev)
	if (prev >= curr) return prev;

	// אחרת ממשיכים שמאלה על שאר המספר
	return isAscendingDigits(n / 10);
}
