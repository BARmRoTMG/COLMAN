#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"

//Default
Bank::Bank()
{
	m_name = nullptr;
	m_account = nullptr;
	m_bankCode = 0;
	m_numbeOfAccounts = 0;
	m_totalBalance = 0.0;
}

//Parameters
Bank::Bank(const char* name, int code)
{
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
	m_account = nullptr;
	m_bankCode = code;
	m_numbeOfAccounts = 0;
	m_totalBalance = 0.0;
}

//Destructor
Bank::~Bank()
{
	if (m_name)
	{
		delete[] m_name;
		m_name = nullptr;
	}

	if (m_account)
	{
		for (int i = 0; i < m_numbeOfAccounts; ++i)
		{
			delete m_account[i];  // כל חשבון שיצרנו בהעתקה
		}
		delete[] m_account;
		m_account = nullptr;
	}

	m_numbeOfAccounts = 0;
	m_totalBalance = 0.0;
	m_bankCode = 0;
}

void Bank::SetBankName(const char* name)
{
	delete[] m_name;
	if (name)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
	else
	{
		m_name = nullptr;
	}
}

void Bank::SetAccount(Account** account, int numberOfAccounts)
{
	// נקה קודם
	if (m_account)
	{
		for (int i = 0; i < m_numbeOfAccounts; ++i)
		{
			delete m_account[i];
		}
		delete[] m_account;
	}

	if (account && numberOfAccounts > 0)
	{
		m_account = new Account * [numberOfAccounts];
		for (int i = 0; i < numberOfAccounts; ++i)
		{
			m_account[i] = new Account(*account[i]); // deep copy
		}
		m_numbeOfAccounts = numberOfAccounts;
	}
	else
	{
		m_account = nullptr;
		m_numbeOfAccounts = 0;
	}
}

void Bank::SetTotal(double total) { m_totalBalance = total; }
void Bank::SetCode(int code) { m_bankCode = code; }

const char* Bank::GetBankName() const { return m_name; }
Account** Bank::GetAccounts() const { return m_account; }
int         Bank::GetNumberOfAccounts() const { return m_numbeOfAccounts; }
double      Bank::GetTotal() const { return m_totalBalance; }
int         Bank::GetCode() const { return m_bankCode; }

void Bank::AddAccount(const Account& account)
{
	// --- בדיקת כפילות "זהות מלאה" (מס' בעלי חשבון, סדר ה-IDs, יתרה) ---
	Person** newOwners = account.GetPersons();
	int      newCount = account.GetTotalPersons();

	for (int i = 0; i < m_numbeOfAccounts; ++i)
	{
		Account* ex = m_account[i];
		if (ex->GetTotalPersons() != newCount) continue;
		if (ex->GetBalance() != account.GetBalance()) continue;

		Person** exOwners = ex->GetPersons();
		bool same = true;
		for (int j = 0; j < newCount; ++j)
		{
			if (exOwners[j]->GetId() != newOwners[j]->GetId()) { same = false; break; }
		}
		if (same)
		{
			// כבר יש חשבון זהה → לא מוסיפים
			return;
		}
	}

	// --- הוספה בטוחה: לא מעתיקים שורדים, רק מרחיבים את מערך המצביעים ---
	Account** next = new Account * [m_numbeOfAccounts + 1];
	for (int i = 0; i < m_numbeOfAccounts; ++i)
		next[i] = m_account[i];                    // לא עושים deep copy לשורדים

	next[m_numbeOfAccounts] = new Account(account);
	next[m_numbeOfAccounts]->SetAccountNumber(m_numbeOfAccounts + 1);

	delete[] m_account;                            // מחליפים רק את מערך המצביעים
	m_account = next;

	m_numbeOfAccounts += 1;
	m_totalBalance += account.GetBalance();
}


void Bank::AddAccount(const Person& per, double amount)
{
	Account acc(per, amount);
	this->AddAccount(acc);
}

void Bank::AddPerson(const Person& newPerson, const Account& account, double amount)
{
	for (int i = 0; i < m_numbeOfAccounts; ++i)
	{
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
		{
			m_account[i]->AddPerson(newPerson, amount);
			if (amount > 0.0) m_totalBalance += amount; // משקף את השינוי ביתרה הכוללת
			return;
		}
	}
}

void Bank::DeleteAccount(const Account& account)
{
	if (!m_account || m_numbeOfAccounts == 0) return;

	const int targetNo = account.GetAccountNumber();

	int idx = -1;
	for (int i = 0; i < m_numbeOfAccounts; ++i)
	{
		if (m_account[i] && m_account[i]->GetAccountNumber() == targetNo) { idx = i; break; }
	}
	if (idx == -1) return;

	m_totalBalance -= m_account[idx]->GetBalance();
	delete m_account[idx];                // מוחקים רק את האובייקט הזה

	// דחיסה במקום – לא מעתיקים שורדים!
	for (int i = idx + 1; i < m_numbeOfAccounts; ++i)
		m_account[i - 1] = m_account[i];

	m_numbeOfAccounts--;

	// התאמת מערך המצביעים בלבד
	Account** next = (m_numbeOfAccounts > 0) ? new Account * [m_numbeOfAccounts] : nullptr;
	for (int i = 0; i < m_numbeOfAccounts; ++i) next[i] = m_account[i];
	delete[] m_account;
	m_account = next;
}

void Bank::DeletePerson(const Person& p)
{
	if (!m_account || m_numbeOfAccounts == 0) return;

	int write = 0;
	double newTotal = 0.0;

	for (int i = 0; i < m_numbeOfAccounts; ++i)
	{
		Account* acc = m_account[i];
		acc->DeletePerson(p);

		if (acc->GetTotalPersons() == 0)
		{
			m_totalBalance -= acc->GetBalance();
			delete acc;                      // החשבון התרוקן → מוחקים אותו
		}
		else
		{
			m_account[write++] = acc;        // החשבון שורד → מזיזים קדימה
			newTotal += acc->GetBalance();
		}
	}

	Account** next = (write > 0) ? new Account * [write] : nullptr;
	for (int i = 0; i < write; ++i) next[i] = m_account[i];
	delete[] m_account;

	m_account = next;
	m_numbeOfAccounts = write;
	m_totalBalance = newTotal;
}