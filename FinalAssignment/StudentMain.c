#include "exam.h"

int count1 = 0;

void fx1()
{
	count1++;
}

//השוואת מערכים 
int arrays_equal(int* a, int* b, int n)
{
	for (int i = 0; i < n; i++)
		if (a[i] != b[i]) return 0;
	return 1;
}
// השוואת מחרוזות
int strings_equal_safe(const char* a, const char* b)
{
	// שני מצביעים NULL נחשבים שווים
	if (!a && !b) return 1;

	// אם רק אחד NULL – לא שווה
	if (!a || !b) return 0;

	// השוואה תו-תו עד סוף שתי המחרוזות
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0')
	{
		if (a[i] != b[i])
			return 0;
		++i;
	}

	// שווים אם שניהם הסתיימו יחד
	return (a[i] == '\0' && b[i] == '\0');
}
//Helpers for Q8/Q9/Q10
static Trip* make_trip(const char* start, const char* end, int d, int m, int y, int cost)
{
	Trip* t = (Trip*)malloc(sizeof(Trip));
	if (!t) return NULL;
	t->startTrip = start ? (char*)malloc(strlen(start) + 1) : NULL;
	t->endTrip = end ? (char*)malloc(strlen(end) + 1) : NULL;
	if ((start && !t->startTrip) || (end && !t->endTrip))
	{
		if (t->startTrip) free(t->startTrip);
		if (t->endTrip) free(t->endTrip);
		free(t);
		return NULL;
	}
	if (start) strcpy(t->startTrip, start);
	if (end)   strcpy(t->endTrip, end);
	t->dateTrip.day = d; t->dateTrip.month = m; t->dateTrip.year = y;
	t->costTrip = cost;
	return t;
}
static void free_trip(Trip* t)
{
	if (!t) return;
	free(t->startTrip);
	free(t->endTrip);
	free(t);
}
static Customer* make_customer(const char* name, const char* id, const char* email, const char* phone)
{
	Customer* c = (Customer*)malloc(sizeof(Customer));
	if (!c) return NULL;
	memset(c, 0, sizeof(*c));

	// מצביעים שמחייבים הקצאה
	c->fullName = name ? (char*)malloc(strlen(name) + 1) : NULL;
	c->email = email ? (char*)malloc(strlen(email) + 1) : NULL;

	if ((name && !c->fullName) ||
		(email && !c->email))
	{
		if (c->fullName) free(c->fullName);
		if (c->email)    free(c->email);
		free(c);
		return NULL;
	}

	if (name)  strcpy(c->fullName, name);
	if (email) strcpy(c->email, email);

	// ID הוא מערך בגודל 10 → מעתיקים בבטחה ומשאירים NUL בסוף
	if (id)
	{
		strncpy(c->ID, id, sizeof(c->ID) - 1);
		c->ID[sizeof(c->ID) - 1] = '\0';
	}
	else
	{
		c->ID[0] = '\0';
	}

	// cellPhone הוא מערך בגודל 11 → לא מקצים; מעתיקים ישירות
	if (phone)
	{
		strncpy(c->cellPhone, phone, sizeof(c->cellPhone) - 1);
		c->cellPhone[sizeof(c->cellPhone) - 1] = '\0';
	}
	else
	{
		c->cellPhone[0] = '\0';
	}

	c->trips = NULL;
	c->numTrips = 0;
	return c;
}
static void free_customer_deep(Customer* c)
{
	if (!c) return;

	if (c->trips)
	{
		for (int i = 0; i < c->numTrips; ++i)
		{
			Trip* ti = c->trips[i];
			if (!ti) continue;

			// בדוק אם כבר הופיע קודם -> אם כן דלג כדי לא לשחרר פעמיים
			int seen = 0;
			for (int j = 0; j < i; ++j)
			{
				if (c->trips[j] == ti) { seen = 1; break; }
			}
			if (!seen)
			{
				free_trip(ti);   // משחרר startTrip/endTrip ו-Trip*
			}
		}
		free(c->trips);
	}

	free(c->fullName);
	free(c->email);
	// לא משחררים c->cellPhone או c->ID (מערכים פנימיים)
	free(c);
}

static MoovitDB* make_db(int n)
{
	MoovitDB* db = (MoovitDB*)malloc(sizeof(MoovitDB));
	if (!db) return NULL;
	db->numCustomers = n;
	db->customers = n > 0 ? (Customer**)calloc(n, sizeof(Customer*)) : NULL;
	if (n > 0 && !db->customers) { free(db); return NULL; }
	return db;
}
static void free_db_deep(MoovitDB* db)
{
	if (!db) return;
	if (db->customers)
	{
		for (int i = 0; i < db->numCustomers; ++i) free_customer_deep(db->customers[i]);
		free(db->customers);
	}
	free(db);
}
static int append_trip_direct(Customer* c, Trip* t)
{
	Trip** bigger = (Trip**)realloc(c->trips, (size_t)(c->numTrips + 1) * sizeof(Trip*));
	if (!bigger) return 0;
	c->trips = bigger;
	c->trips[c->numTrips] = t;
	c->numTrips += 1;
	return 1;
}
static int g_pass_q = 0, g_fail_q = 0;
#define ASSERT_TRUE_Q(cond, msg) do { \
    if (!(cond)) { ++g_fail_q; printf("  [FAIL] %s\n", msg); } \
    else { ++g_pass_q; printf("  [PASS] %s\n", msg); } \
} while (0)

void TestQ1(int m[][COLS], int rows, const int expected[], int n)
{
	int* got = weightedEvenColumnSums(m, rows);

	/* מקרה קצה: אם rows<=0 או שהמצביע למטריצה NULL – נצפה לקבל NULL */
	if (rows <= 0 || m == NULL)
	{
		if (got != NULL)
		{
			printf("your weightedEvenColumnSums(matrix, %d) should return NULL for invalid input (-2)\n", rows);
			free(got);
		}
		return;
	}

	/* במקרה רגיל – אם קיבלנו NULL זה אומר כשלון בחישוב */
	if (!got)
	{
		printf("your weightedEvenColumnSums(matrix, %d) returned NULL for valid input (-2)\n", rows);
		return;
	}

	/* השוואת הערכים המוחזרים לערכים הצפויים */
	for (int i = 0; i < n; ++i)
	{
		if (got[i] != expected[i])
		{
			printf("your weightedEvenColumnSums(matrix, %d) function is wrong (-2)\n", rows);
			free(got);
			return;
		}
	}

	/* אם הכל תקין – משחררים את הזיכרון */
	free(got);
}

void TestQ2(int in[], int size, int k, int expected[], int n)
{
	int arr[100];  // נשתמש בהעתק כדי לא לשנות את המערך המקורי בבדיקה

	// מעתיקים את כל הערכים למערך arr
	for (int i = 0; i < size; i++)
		arr[i] = in[i];

	// מפעילים את הפונקציה הנבדקת
	rotate_right(arr, size, k);

	// השוואה מול התוצאה הצפויה
	if (!arrays_equal(arr, expected, n))
	{
		printf("your rotate_right(arr, %d, %d) function is wrong (-2)\n", size, k);
	}
}

void TestQ3(const char* s1, const char* s2, int expected)
{
	// קריאה לפונקציה הנבדקת
	int got = areAnagrams(s1, s2);

	// בדיקה מול התוצאה הצפויה
	if (got != expected)
	{
		// הדפסה בטוחה גם כאשר אחד המצביעים הוא NULL
		const char* a = (s1 ? s1 : "(null)");
		const char* b = (s2 ? s2 : "(null)");
		printf("your areAnagrams(\"%s\", \"%s\") function is wrong (-2)\n", a, b);
	}
}

void TestQ4(const char* in, const char* expected)
{
	// קריאה לפונקציה הנבדקת
	char* got = removeDuplicates(in);

	// בדיקה מול התוצאה הצפויה
	if (!strings_equal_safe(got, expected))
	{
		const char* a = (in ? in : "(null)");
		const char* e = (expected ? expected : "(null)");
		const char* g = (got ? got : "(null)");
		printf("your removeDuplicates(\"%s\") returned \"%s\" but expected \"%s\" (-2)\n", a, g, e);
	}

	// שחרור זיכרון
	if (got) free(got);
}

void TestQ5(const char* in, const char* expected)
{
	char* got = sortByFrequency(in);
	int ok = (got && strcmp(got, expected) == 0);

	if (!ok)
		printf("your sortByFrequency(\"%s\") function is wrong (-2)\n", in);

	if (got) free(got);
}


int main()
{
	printf("Test Start\n");

#pragma region Q1

	/*---------------------------Q1---------------------------*/
	printf("\nQ1 - weightedEvenColumnSums\n");

	/* 1) דוגמת המטלה */
	int m1[3][COLS] = {
		{2,7,3,4,1},
		{5,6,8,2,9},
		{1,3,2,5,4}
	};
	int exp1[3] = { 42, 198, 35 };
	TestQ1(m1, 3, exp1, 3);

	/* 2) שורה אחת בלבד */
	int m2[1][COLS] = { {10, 9, 8, 7, 6} };
	int exp2[1] = { 240 }; /* (10+8+6)*10 */
	TestQ1(m2, 1, exp2, 1);

	/* 3) ערכים שליליים */
	int m3[2][COLS] = {
		{-2,-7,-3,-4,-1},  /* even=-6, max=-1 => 6 */
		{-5,-6,-8,-2,-9}   /* even=-22, max=-2 => 44 */
	};
	int exp3[2] = { 6, 44 };
	TestQ1(m3, 2, exp3, 2);

	/* 4) אפסים בלבד */
	int m4[1][COLS] = { {0,0,0,0,0} };
	int exp4[1] = { 0 };
	TestQ1(m4, 1, exp4, 1);

	/* 5) מקסימום בעמודה זוגית */
	int m5[1][COLS] = { {5,1,9,0,2} };
	int exp5[1] = { 144 }; /* even=16, max=9 */
	TestQ1(m5, 1, exp5, 1);

	/* 6) מקסימום בעמודה אי-זוגית */
	int m6[1][COLS] = { {3,8,7,6,5} };
	int exp6[1] = { 120 }; /* even=15, max=8 */
	TestQ1(m6, 1, exp6, 1);

	/* 7) מקסימום מופיע כמה פעמים */
	int m7[1][COLS] = { {4,9,4,1,9} };
	int exp7[1] = { 153 }; /* even=17, max=9 */
	TestQ1(m7, 1, exp7, 1);

	/* 8) שורות עם תוצאה 0 בשורה אחת, ו־5 בשורה שנייה */
	int m8[2][COLS] = {
		{0,1,0,1,0}, /* even sum=0, max=1 => 0 */
		{0,0,0,5,1}  /* even sum=0+0+1=1, max=5 => 5 */
	};
	int exp8[2] = { 0, 5 };
	TestQ1(m8, 2, exp8, 2);

	/* 9) סכום קטן, מקסימום גדול */
	int m9[1][COLS] = { {1,100,1,100,1} };
	int exp9[1] = { 300 }; /* even sum=3, max=100 */
	TestQ1(m9, 1, exp9, 1);

	/* 10) סכום גדול, מקסימום קטן */
	int m10[1][COLS] = { {5,1,5,1,5} };
	int exp10[1] = { 75 }; /* even sum=15, max=5 */
	TestQ1(m10, 1, exp10, 1);
#pragma endregion

#pragma region Q2
	/*---------------------------Q2---------------------------*/

	printf("\nQ2 - rotate_right\n");

	/* 1) דוגמה מהמטלה */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 4,1,2,3 };
		TestQ2(a, 4, 1, e, 4);
	}

	/* 2) k=0 (אין שינוי) */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 1,2,3,4 };
		TestQ2(a, 4, 0, e, 4);
	}

	/* 3) k=size (גם אין שינוי) */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 1,2,3,4 };
		TestQ2(a, 4, 4, e, 4);
	}

	/* 4) k>size (בדוק מודולו) */
	{
		int a[4] = { 1,2,3,4 };
		int e[4] = { 3,4,1,2 }; // k=6 -> כמו k=2
		TestQ2(a, 4, 6, e, 4);
	}

	/* 5) מערך בגודל 1 */
	{
		int a[1] = { 7 };
		int e[1] = { 7 };
		TestQ2(a, 1, 5, e, 1);
	}

	/* 6) מערך בגודל 2 */
	{
		int a[2] = { 9,8 };
		int e[2] = { 8,9 };
		TestQ2(a, 2, 1, e, 2);
	}

	/* 7) מספר שלילי ברוטציה */
	{
		int a[5] = { 10,20,30,40,50 };
		int e[5] = { 20,30,40,50,10 }; // k=-1 -> סיבוב שמאלה אחד
		TestQ2(a, 5, -1, e, 5);
	}

	/* 8) ערכים שליליים במערך */
	{
		int a[5] = { -1,-2,-3,-4,-5 };
		int e[5] = { -2,-3,-4,-5,-1 }; // k=4 -> כמו k=-1
		TestQ2(a, 5, 4, e, 5);
	}

	/* 9) k=2 בגודל 5 */
	{
		int a[5] = { 1,2,3,4,5 };
		int e[5] = { 4,5,1,2,3 };
		TestQ2(a, 5, 2, e, 5);
	}

	/* 10) מערך עם חזרות — k=4 (שקול לשמאלה 2) */
	{
		int a[6] = { 1,1,2,2,3,3 };
		int e[6] = { 2,2,3,3,1,1 };  // תיקון כאן
		TestQ2(a, 6, 4, e, 6);
	}

#pragma endregion

#pragma region Q3
	printf("\nQ3 - areAnagrams\n");

	// 1) דוגמת אנגרמה בסיסית
	TestQ3("listen", "silent", 1);

	// 2) אות אחת שונה -> לא אנגרמה
	TestQ3("hello", "hella", 0);

	// 3) זהות מלאה של המחרוזות
	TestQ3("aa", "aa", 1);

	// 4) אורכים שונים -> לא אנגרמה
	TestQ3("ab", "aba", 0);

	// 5) חזרות של אותיות בסדרים שונים
	TestQ3("aabbcc", "abcabc", 1);

	// 6) רגישות לאותיות גדולות/קטנות (Case-Sensitive כברירת מחדל)
	TestQ3("Abc", "abc", 0);

	// 7) מחרוזות ריקות -> אנגרמה תקפה
	TestQ3("", "", 1);

	// 8) ריקה מול לא-ריקה -> לא אנגרמה
	TestQ3("", "a", 0);

	// 9) כולל תווים לא-אותיים (כל תו נספר) – כאן זה כן אנגרמה
	TestQ3("rail!", "lair!", 1);

	// 10) מקרה קצה: אחד המצביעים NULL -> לא אנגרמה
	TestQ3(NULL, "abc", 0);
#pragma endregion

#pragma region Q4
	/*---------------------------Q4---------------------------*/

	printf("\nQ4 - removeDuplicates\n");

	// 1) דוגמה מהמטלה
	TestQ4("programming", "poain");

	// 2) מחרוזת ריקה -> נשאר ריק
	TestQ4("", "");

	// 3) כל התווים זהים -> הכל נמחק
	TestQ4("aaaa", "");

	// 4) כולם ייחודיים -> נשאר אותו הדבר
	TestQ4("abc", "abc");

	// 5) חזרות מרובות + ייחודי יחיד בסוף
	TestQ4("aabbccdde", "e");

	// 6) ערבוב חזרות + ייחודיים (סדר נשמר)
	TestQ4("abac", "bc");

	// 7) רגישות לאותיות גדולות/קטנות (A ו-a שונים)
	TestQ4("Aa", "Aa");

	// 8) תווים לא-אותיים – נשארים אם ייחודיים
	TestQ4("a!a?bb ", "!? ");

	// 9) ספרות וקישוטים
	TestQ4("1122334455x", "x");

	// 10) קלט NULL -> פלט NULL
	TestQ4(NULL, NULL);

#pragma endregion

#pragma region Q5
	/*---------------------------Q5---------------------------*/

	printf("\nQ5 - sortByFrequency\n");

	/* 1) דוגמת המטלה #1 */
	TestQ5("aabcccdeee", "ccceeeaabd");

	/* 2) דוגמת המטלה #2 */
	TestQ5("tree", "eetr");

	/* 3) מחרוזת ריקה */
	TestQ5("", "");

	/* 4) תו יחיד */
	TestQ5("x", "x");

	/* 5) כל התווים שונים – כולם תדירות 1, שומרים סדר מקור */
	TestQ5("abcde", "abcde");

	/* 6) רגיש לרישיות ותיקו – קדימות לפי הופעה ראשונה */
	TestQ5("bbAa", "bbAa");      /* b:2, A:1 (idx2), a:1 (idx3) */

	/* 7) mississippi – i:4 (idx1) לפני s:4 (idx2), אח"כ p:2, אח"כ m:1 */
	TestQ5("mississippi", "iiiissssppm");

	/* 8) רישיות מעורבות ותיקו כפול */
	TestQ5("AaAaBb", "AAaaBb");  /* A:2 (idx0), a:2 (idx1), B:1, b:1 */

	/* 9) ספרות עם תיקו גדול – '1' הופיע לפני '2' */
	TestQ5("1122332211", "1111222233");

	/* 10) סימני פיסוק ותיקו – '!' לפני '?' במקור */
	TestQ5("a!!bbb??", "bbb!!??a");

#pragma endregion

#pragma region Q6
	/*---------------------------Q6---------------------------*/
	printf("\nQ6 - binary_as_number\n");

	// 1) דוגמת המטלה
	if (binary_as_number(5) != 101)
		printf("your binary_as_number(5) function is wrong (-2)\n");     // 5 -> 101

	// 2) 0
	if (binary_as_number(0) != 0)
		printf("your binary_as_number(0) function is wrong (-2)\n");

	// 3) חזקת 2
	if (binary_as_number(8) != 1000)
		printf("your binary_as_number(8) function is wrong (-2)\n");

	// 4) מספר קטן נוסף
	if (binary_as_number(2) != 10)
		printf("your binary_as_number(2) function is wrong (-2)\n");

	// 5) מספר עם הרבה 1-ים (7 = 111₂)
	if (binary_as_number(7) != 111)
		printf("your binary_as_number(7) function is wrong (-2)\n");

	// 6) 13 = 1101₂
	if (binary_as_number(13) != 1101)
		printf("your binary_as_number(13) function is wrong (-2)\n");

	// 7) 1
	if (binary_as_number(1) != 1)
		printf("your binary_as_number(1) function is wrong (-2)\n");

	// 8) 16 = 10000₂
	if (binary_as_number(16) != 10000)
		printf("your binary_as_number(16) function is wrong (-2)\n");

	// 9) 19 = 10011₂
	if (binary_as_number(19) != 10011)
		printf("your binary_as_number(19) function is wrong (-2)\n");

	// 10) 31 = 11111₂
	if (binary_as_number(31) != 11111)
		printf("your binary_as_number(31) function is wrong (-2)\n");
#pragma endregion

#pragma region Q7
	/*---------------------------Q7---------------------------*/
	printf("\nQ7 - isAscendingDigits\n");

	// 1) כל הספרות עולות
	if (isAscendingDigits(123579) != 10)
		printf("your isAscendingDigits(123579) function is wrong (-2)\n"); // 1<2<3<5<7<9 → 10

	// 2) שבירה ראשונה ב-4 (כי 5 לא קטן מ-4)
	if (isAscendingDigits(13542) != 4)
		printf("your isAscendingDigits(13542) function is wrong (-2)\n");

	// 3) חד-ספרתי
	if (isAscendingDigits(7) != 10)
		printf("your isAscendingDigits(7) function is wrong (-2)\n");

	// 4) שתי ספרות עולות
	if (isAscendingDigits(19) != 10)
		printf("your isAscendingDigits(19) function is wrong (-2)\n");

	// 5) שתי ספרות שוות – שובר מיד (לא עולה בקפדנות)
	if (isAscendingDigits(11) != 1)
		printf("your isAscendingDigits(11) function is wrong (-2)\n");

	// 6) ירידה מיד בהתחלה
	if (isAscendingDigits(31) != 3)
		printf("your isAscendingDigits(31) function is wrong (-2)\n");

	// 7) שבירה מאוחרת
	if (isAscendingDigits(123454567) != 5)
		printf("your isAscendingDigits(123454567) function is wrong (-2)\n"); // השבירה בזוג 5,4 → מחזיר 5

	// 8) רצף ארוך עולה
	if (isAscendingDigits(123456789) != 10)
		printf("your isAscendingDigits(123456789) function is wrong (-2)\n");

	// 9) ספרה שווה לשכנה (שבירה) באמצע
	if (isAscendingDigits(122345) != 2)
		printf("your isAscendingDigits(122345) function is wrong (-2)\n");

	// 10) עוד שבירה בסוף
	if (isAscendingDigits(246788) != 8)
		printf("your isAscendingDigits(246788) function is wrong (-2)\n"); // 8 לא קטן מ-8 → מחזיר 8

#pragma endregion

#pragma region Q8
	/*---------------------------Q8---------------------------*/
	printf("\nQ8 - getMostExpensiveTrips\n");

	/* T1: לקוח יחיד, נסיעה יחידה */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		Trip* t = make_trip("TLV", "NYC", 1, 1, 2025, 100);
		append_trip_direct(db->customers[0], t);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == t, "Q8 T1: single customer single trip");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T2: לקוח יחיד, כמה נסיעות, בוחר היקרה */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		Trip* t1 = make_trip("TLV", "ROM", 1, 1, 2025, 200);
		Trip* t2 = make_trip("TLV", "PAR", 2, 1, 2025, 350); /* max */
		Trip* t3 = make_trip("TLV", "BER", 3, 1, 2025, 300);
		append_trip_direct(db->customers[0], t1);
		append_trip_direct(db->customers[0], t2);
		append_trip_direct(db->customers[0], t3);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == t2, "Q8 T2: pick highest cost");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T3: שני לקוחות, השני בלי נסיעות -> NULL */
	{
		MoovitDB* db = make_db(2);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[1] = make_customer("B", "2", "b@x", "050");
		Trip* t = make_trip("A", "B", 1, 1, 2025, 111);
		append_trip_direct(db->customers[0], t);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == t && tops[1] == NULL, "Q8 T3: customer without trips -> NULL");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T4: כל הנסיעות NULL (חורים) -> NULL */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[0]->trips = (Trip**)calloc(3, sizeof(Trip*));
		db->customers[0]->numTrips = 3;
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == NULL, "Q8 T4: all trip pointers NULL -> result NULL");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T5: שוויון בעלות - נבחרת הראשונה */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		Trip* t1 = make_trip("X", "Y", 1, 1, 2025, 500);
		Trip* t2 = make_trip("X", "Z", 1, 1, 2025, 500);
		append_trip_direct(db->customers[0], t1);
		append_trip_direct(db->customers[0], t2);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == t1, "Q8 T5: tie -> pick first");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T6: סלוט של לקוח NULL */
	{
		MoovitDB* db = make_db(2);
		db->customers[0] = NULL;
		db->customers[1] = make_customer("B", "2", "b@x", "050");
		Trip* t = make_trip("S", "E", 1, 1, 2025, 90);
		append_trip_direct(db->customers[1], t);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == NULL && tops[1] == t, "Q8 T6: null customer slot handled");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T7: DB ריק -> NULL */
	{
		MoovitDB* db = make_db(0);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops == NULL, "Q8 T7: empty DB -> NULL");
		free_db_deep(db);
	}

	/* T8: db == NULL -> NULL */
	{
		Trip** tops = getMostExpensiveTrips(NULL);
		ASSERT_TRUE_Q(tops == NULL, "Q8 T8: NULL db -> NULL");
	}

	/* T9: עלויות גדולות מאוד */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		Trip* t1 = make_trip("X", "Y", 1, 1, 2025, INT_MAX - 1);
		Trip* t2 = make_trip("X", "Z", 1, 1, 2025, INT_MAX);
		append_trip_direct(db->customers[0], t1);
		append_trip_direct(db->customers[0], t2);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == t2, "Q8 T9: very large costs");
		if (tops) free(tops);
		free_db_deep(db);
	}

	/* T10: דאטה מעורב */
	{
		MoovitDB* db = make_db(3);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[1] = make_customer("B", "2", "b@x", "050");
		db->customers[2] = make_customer("C", "3", "c@x", "050");
		Trip* a1 = make_trip("A", "B", 1, 1, 2025, 10);
		Trip* a2 = make_trip("A", "C", 1, 1, 2025, 99);
		Trip* b1 = make_trip("B", "C", 1, 1, 2025, 5);
		append_trip_direct(db->customers[0], a1);
		append_trip_direct(db->customers[0], a2);
		append_trip_direct(db->customers[1], b1);
		Trip** tops = getMostExpensiveTrips(db);
		ASSERT_TRUE_Q(tops && tops[0] == a2 && tops[1] == b1 && tops[2] == NULL, "Q8 T10: mixed data");
		if (tops) free(tops);
		free_db_deep(db);
	}
#pragma endregion

#pragma region Q9
	/*---------------------------Q9---------------------------*/
	printf("\nQ9 - addTripPointerToCustomer\n");

	/* T1: הוספה ראשונה ללקוח ריק */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		Trip* t = make_trip("X", "Y", 1, 1, 2025, 1);
		int res = addTripPointerToCustomer(c, t);
		ASSERT_TRUE_Q(res == 1 && c->numTrips == 1 && c->trips[0] == t, "Q9 T1: add first trip");
		free_customer_deep(c);
	}

	/* T2: הוספה שניה ושמירת סדר */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		Trip* t1 = make_trip("X", "Y", 1, 1, 2025, 1);
		Trip* t2 = make_trip("X", "Z", 1, 1, 2025, 2);
		addTripPointerToCustomer(c, t1);
		int res = addTripPointerToCustomer(c, t2);
		ASSERT_TRUE_Q(res == 2 && c->numTrips == 2 && c->trips[1] == t2 && c->trips[0] == t1, "Q9 T2: add second trip keeps order");
		free_customer_deep(c);
	}

	/* T3: newTrip == NULL -> -1 */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		int res = addTripPointerToCustomer(c, NULL);
		ASSERT_TRUE_Q(res == -1 && c->numTrips == 0, "Q9 T3: NULL newTrip");
		free_customer_deep(c);
	}

	/* T4: cust == NULL -> -1 */
	{
		Trip* t = make_trip("X", "Y", 1, 1, 2025, 1);
		int res = addTripPointerToCustomer(NULL, t);
		ASSERT_TRUE_Q(res == -1, "Q9 T4: NULL customer");
		free_trip(t);
	}

	/* T5: הוספת 5 נסיעות */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		int ok = 1;
		for (int i = 0; i < 5; ++i)
		{
			Trip* t = make_trip("S", "E", 1, 1, 2025, i);
			int res = addTripPointerToCustomer(c, t);
			if (res != (i + 1)) ok = 0;
		}
		ASSERT_TRUE_Q(ok && c->numTrips == 5, "Q9 T5: add 5 trips grows correctly");
		free_customer_deep(c);
	}

	/* T6: pointers preserved after growth */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		Trip* t1 = make_trip("1", "x", 1, 1, 2025, 10);
		Trip* t2 = make_trip("2", "x", 1, 1, 2025, 20);
		Trip* t3 = make_trip("3", "x", 1, 1, 2025, 30);
		addTripPointerToCustomer(c, t1);
		addTripPointerToCustomer(c, t2);
		int res = addTripPointerToCustomer(c, t3);
		int ok = (res == 3) && (c->trips[0] == t1) && (c->trips[1] == t2) && (c->trips[2] == t3);
		ASSERT_TRUE_Q(ok, "Q9 T6: pointers preserved after growth");
		free_customer_deep(c);
	}

	/* T7: INT_MAX guard (אם ממומש) */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		c->numTrips = INT_MAX;
		Trip* t = make_trip("X", "Y", 1, 1, 2025, 1);
		int res = addTripPointerToCustomer(c, t);
		ASSERT_TRUE_Q(res == -1, "Q9 T7: INT_MAX guard");
		free_trip(t);
		c->numTrips = 0;
		free_customer_deep(c);
	}

	/* T8: same pointer multiple times */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		Trip* t = make_trip("R", "S", 1, 1, 2025, 7);
		addTripPointerToCustomer(c, t);
		int res = addTripPointerToCustomer(c, t);
		ASSERT_TRUE_Q(res == 2 && c->trips[0] == t && c->trips[1] == t, "Q9 T8: same pointer multiple times");
		free_customer_deep(c);
	}

	/* T9: holes in existing array (NULL באמצע) – הוספה בסוף */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		c->trips = (Trip**)calloc(2, sizeof(Trip*)); /* [NULL, NULL] */
		c->numTrips = 2;
		Trip* t = make_trip("X", "Y", 1, 1, 2025, 42);
		int res = addTripPointerToCustomer(c, t);
		ASSERT_TRUE_Q(res == 3 && c->trips[2] == t && c->trips[0] == NULL && c->trips[1] == NULL, "Q9 T9: append after holes");
		free_customer_deep(c);
	}

	/* T10: return value == numTrips החדש */
	{
		Customer* c = make_customer("A", "1", "a@x", "050");
		Trip* t1 = make_trip("1", "2", 1, 1, 2025, 1);
		Trip* t2 = make_trip("1", "3", 1, 1, 2025, 1);
		int r1 = addTripPointerToCustomer(c, t1);
		int r2 = addTripPointerToCustomer(c, t2);
		ASSERT_TRUE_Q(r1 == 1 && r2 == 2 && c->numTrips == 2, "Q9 T10: return value matches numTrips");
		free_customer_deep(c);
	}
#pragma endregion

#pragma region Q10
	/*---------------------------Q10---------------------------*/
	printf("\nQ10 - findTopVisitorToDestination\n");

	/* T1: בסיסי - לקוח עם הכי הרבה נסיעות ליעד */
	{
		MoovitDB* db = make_db(2);
		db->customers[0] = make_customer("Alice", "1", "a@x", "050");
		db->customers[1] = make_customer("Bob", "2", "b@x", "050");
		append_trip_direct(db->customers[0], make_trip("TLV", "NYC", 1, 1, 2025, 100));
		append_trip_direct(db->customers[0], make_trip("ROM", "PAR", 2, 1, 2025, 50));
		append_trip_direct(db->customers[1], make_trip("TLV", "NYC", 1, 1, 2025, 70));
		append_trip_direct(db->customers[1], make_trip("BER", "NYC", 2, 1, 2025, 80));
		append_trip_direct(db->customers[1], make_trip("AMS", "NYC", 3, 1, 2025, 90)); /* Bob: 3x */
		char* name = findTopVisitorToDestination(db, "NYC");
		ASSERT_TRUE_Q(name && strcmp(name, "Bob") == 0, "Q10 T1: Bob has most NYC trips");
		free_db_deep(db);
	}

	/* T2: אין אף נסיעה ליעד -> NULL */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		append_trip_direct(db->customers[0], make_trip("TLV", "ROM", 1, 1, 2025, 1));
		char* name = findTopVisitorToDestination(db, "PAR");
		ASSERT_TRUE_Q(name == NULL, "Q10 T2: no trips to destination -> NULL");
		free_db_deep(db);
	}

	/* T3: כמה לקוחות, ספירות שונות */
	{
		MoovitDB* db = make_db(3);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[1] = make_customer("B", "2", "b@x", "050");
		db->customers[2] = make_customer("C", "3", "c@x", "050");
		append_trip_direct(db->customers[0], make_trip("X", "PAR", 1, 1, 2025, 1));
		append_trip_direct(db->customers[1], make_trip("Y", "PAR", 1, 1, 2025, 1));
		append_trip_direct(db->customers[1], make_trip("Z", "PAR", 2, 1, 2025, 1)); /* B: 2x */
		append_trip_direct(db->customers[2], make_trip("Q", "BER", 1, 1, 2025, 1));
		char* name = findTopVisitorToDestination(db, "PAR");
		ASSERT_TRUE_Q(name && strcmp(name, "B") == 0, "Q10 T3: B has most to PAR");
		free_db_deep(db);
	}

	/* T4: שוויון – מחזיר הראשון */
	{
		MoovitDB* db = make_db(2);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[1] = make_customer("B", "2", "b@x", "050");
		append_trip_direct(db->customers[0], make_trip("X", "NYC", 1, 1, 2025, 1)); /* A: 2x */
		append_trip_direct(db->customers[0], make_trip("Y", "NYC", 1, 1, 2025, 1));
		append_trip_direct(db->customers[1], make_trip("Z", "NYC", 1, 1, 2025, 1)); /* B: 2x */
		append_trip_direct(db->customers[1], make_trip("W", "NYC", 1, 1, 2025, 1));
		char* name = findTopVisitorToDestination(db, "NYC");
		ASSERT_TRUE_Q(name && strcmp(name, "A") == 0, "Q10 T4: tie -> pick first");
		free_db_deep(db);
	}

	/* T5: רישיות – strcmp (רגיש) */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		append_trip_direct(db->customers[0], make_trip("X", "nyc", 1, 1, 2025, 1));
		char* name = findTopVisitorToDestination(db, "NYC");
		ASSERT_TRUE_Q(name == NULL, "Q10 T5: case-sensitive strcmp");
		free_db_deep(db);
	}

	/* T6: לקוח עם trips == NULL */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		char* name = findTopVisitorToDestination(db, "NYC");
		ASSERT_TRUE_Q(name == NULL, "Q10 T6: customer with NULL trips");
		free_db_deep(db);
	}

	/* T7: numTrips == 0 */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[0]->trips = (Trip**)calloc(2, sizeof(Trip*));
		db->customers[0]->numTrips = 0;
		char* name = findTopVisitorToDestination(db, "NYC");
		ASSERT_TRUE_Q(name == NULL, "Q10 T7: numTrips=0 ignored");
		free_db_deep(db);
	}

	/* T8: endTrip == NULL בתוך Trip */
	{
		MoovitDB* db = make_db(1);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		Trip* t = make_trip("X", NULL, 1, 1, 2025, 1);
		append_trip_direct(db->customers[0], t);
		char* name = findTopVisitorToDestination(db, "NYC");
		ASSERT_TRUE_Q(name == NULL, "Q10 T8: endTrip==NULL ignored");
		free_db_deep(db);
	}

	/* T9: כמה לקוחות – יעד אחר */
	{
		MoovitDB* db = make_db(2);
		db->customers[0] = make_customer("A", "1", "a@x", "050");
		db->customers[1] = make_customer("B", "2", "b@x", "050");
		append_trip_direct(db->customers[0], make_trip("X", "PAR", 1, 1, 2025, 1));
		append_trip_direct(db->customers[1], make_trip("X", "ROM", 1, 1, 2025, 1));
		char* name1 = findTopVisitorToDestination(db, "PAR");
		char* name2 = findTopVisitorToDestination(db, "ROM");
		ASSERT_TRUE_Q(name1 && strcmp(name1, "A") == 0, "Q10 T9a: PAR -> A");
		ASSERT_TRUE_Q(name2 && strcmp(name2, "B") == 0, "Q10 T9b: ROM -> B");
		free_db_deep(db);
	}

	/* T10: db==NULL / destination==NULL */
	{
		char* n1 = findTopVisitorToDestination(NULL, "NYC");
		char* n2 = findTopVisitorToDestination(make_db(0), NULL);
		ASSERT_TRUE_Q(n1 == NULL, "Q10 T10a: NULL db -> NULL");
		ASSERT_TRUE_Q(n2 == NULL, "Q10 T10b: NULL destination -> NULL");
		/* make_db(0) חזר אבל בלי משאבים פנימיים, נשחרר */
		MoovitDB* tmp = make_db(0); free_db_deep(tmp);
	}
#pragma endregion

	printf("\n\ndone\n");
	return 0;
}