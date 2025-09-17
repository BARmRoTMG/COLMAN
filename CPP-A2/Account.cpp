#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"

//Default
Account::Account()
{
	m_transactionList = nullptr;
	m_numberOfTransaction = 0;
	m_persons = nullptr;
	m_totalPersons = 0;
	m_accountNumber = 0;
	m_balance = 0.0;
}

//Persons
Account::Account(Person** persons, int count, double balance)
{
	m_transactionList = nullptr;
	m_numberOfTransaction = 0;

	if (persons && count > 0)
	{
		m_persons = new Person * [count];
		for (int i = 0; i < count; ++i)
		{
			m_persons[i] = new Person(*persons[i]); // deep copy
		}
		m_totalPersons = count;
	}
	else
	{
		m_persons = nullptr;
		m_totalPersons = 0;
	}

	m_accountNumber = 0;
	m_balance = balance;
}

//Single Person
Account::Account(const Person& person, double balance)
{
	m_transactionList = nullptr;
	m_numberOfTransaction = 0;

	m_persons = new Person * [1];
	m_persons[0] = new Person(person); // deep copy
	m_totalPersons = 1;

	m_accountNumber = 0;
	m_balance = balance;
}

//Copy
Account::Account(const Account& other)
{
	m_accountNumber = other.m_accountNumber;
	m_balance = other.m_balance;
	m_totalPersons = other.m_totalPersons;
	m_numberOfTransaction = other.m_numberOfTransaction;

	// בעלי החשבון
	if (m_totalPersons > 0 && other.m_persons)
	{
		m_persons = new Person * [m_totalPersons];
		for (int i = 0; i < m_totalPersons; ++i)
		{
			m_persons[i] = new Person(*other.m_persons[i]); // deep copy
		}
	}
	else
	{
		m_persons = nullptr;
	}

	// היסטוריית טרנזקציות
	if (m_numberOfTransaction > 0 && other.m_transactionList)
	{
		m_transactionList = new Transaction * [m_numberOfTransaction];
		for (int i = 0; i < m_numberOfTransaction; ++i)
		{
			m_transactionList[i] = new Transaction(*other.m_transactionList[i]); // deep copy
		}
	}
	else
	{
		m_transactionList = nullptr;
	}
}

//Destructor
Account::~Account()
{
	clearPersons();
	clearTransactions();
}

void Account::clearPersons()
{
	if (m_persons)
	{
		for (int i = 0; i < m_totalPersons; ++i)
		{
			delete m_persons[i];
		}
		delete[] m_persons;
		m_persons = nullptr;
	}
	m_totalPersons = 0;
}

void Account::clearTransactions()
{
    if (m_transactionList)
    {
        for (int i = 0; i < m_numberOfTransaction; ++i)
        {
            if (m_transactionList[i])
            {
                m_transactionList[i]->SetDate(NULL); // משחרר את ה-char* שבתוך ה-Transaction
                delete m_transactionList[i];
            }
        }

        delete[] m_transactionList;
        m_transactionList = nullptr;
    }
    m_numberOfTransaction = 0;
}

// ===== Setters / Getters =====

void Account::SetPersons(Person** persons, int count)
{
    clearPersons();
    if (persons && count > 0)
    {
        m_persons = new Person * [count];
        for (int i = 0; i < count; ++i)
            m_persons[i] = new Person(*persons[i]);
        m_totalPersons = count;
    }
    else
    {
        m_persons = nullptr;
        m_totalPersons = 0;
    }
}

void Account::SetTransactions(Transaction** newTransaction, int count)
{
    clearTransactions();
    if (newTransaction && count > 0)
    {
        m_transactionList = new Transaction * [count];
        for (int i = 0; i < count; ++i)
        {
            m_transactionList[i] = new Transaction(*newTransaction[i]); // deep copy
        }
        m_numberOfTransaction = count;
    }
    else
    {
        m_transactionList = nullptr;
        m_numberOfTransaction = 0;
    }
}

void Account::SetAccountNumber(int number) { m_accountNumber = number; }
void Account::SetBalance(double balance) { m_balance = balance; }

int           Account::GetAccountNumber() const { return m_accountNumber; }
double        Account::GetBalance() const { return m_balance; }
Person** Account::GetPersons() const { return m_persons; }
int           Account::GetTotalPersons() const { return m_totalPersons; }
Transaction** Account::GetTransactions() { return m_transactionList; }
int           Account::GetNumOfTransactions() { return m_numberOfTransaction; }

// ===== פעולות =====

// לא לשנות יתרה כאן — רק ליצור Transaction ולתת ל-AddTransaction לטפל
void Account::Withdraw(double amount, const char* date)
{
    if (amount <= 0.0) return;
    Transaction t(this, NULL, amount, date);
    AddTransaction(t);
}

void Account::Deposit(double amount, const char* date)
{
    if (amount <= 0.0) return;
    Transaction t(NULL, this, amount, date);
    AddTransaction(t);
}

void Account::AddPerson(const Person& newPerson, double amount)
{
    int oldCount = m_totalPersons;

    Person** next = new Person * [oldCount + 1];
    for (int i = 0; i < oldCount; ++i)
        next[i] = new Person(*m_persons[i]);
    next[oldCount] = new Person(newPerson);

    clearPersons();                 // מאפס ל-0 וזה בסדר כי שמרנו קודם
    m_persons = next;
    m_totalPersons = oldCount + 1;  // ← הצבה מדויקת

    // לפי ה-main: סכום פתיחה ≠ טרנזקציה
    if (amount > 0.0)
    {
        m_balance += amount;        // רק עדכון יתרה, בלי AddTransaction
    }
}

void Account::DeletePerson(const Person& oldPerson)
{
    if (!m_persons || m_totalPersons == 0) return;

    int idx = -1;
    for (int i = 0; i < m_totalPersons; ++i)
    {
        if (m_persons[i]->GetId() == oldPerson.GetId()) { idx = i; break; }
    }
    if (idx == -1) return;

    const int oldCount = m_totalPersons;

    Person** next = nullptr;
    if (oldCount - 1 > 0)
    {
        next = new Person * [oldCount - 1];
        int k = 0;
        for (int i = 0; i < oldCount; ++i)
        {
            if (i == idx) continue;
            next[k++] = new Person(*m_persons[i]);
        }
    }

    clearPersons();               // מאפס ל-0
    m_persons = next;
    m_totalPersons = oldCount - 1; // הצבה מדויקת
}

void Account::AddTransaction(const Transaction& newTransaction)
{
    Account* src = newTransaction.GetSource();
    Account* dst = newTransaction.GetDes();
    double   amt = newTransaction.GetAmount();

    if (src && dst && src == dst)
    {
        Transaction** next = new Transaction * [src->m_numberOfTransaction + 1];
        for (int i = 0; i < src->m_numberOfTransaction; ++i)
            next[i] = new Transaction(*src->m_transactionList[i]);
        next[src->m_numberOfTransaction] = new Transaction(newTransaction);

        if (src->m_transactionList)
        {
            for (int i = 0; i < src->m_numberOfTransaction; ++i)
            {
                src->m_transactionList[i]->SetDate(NULL);
                delete src->m_transactionList[i];
            }
            delete[] src->m_transactionList;
        }
        src->m_transactionList = next;
        src->m_numberOfTransaction += 1;
        return;
    }

    // עדכון יתרות
    if (src) src->m_balance -= amt;
    if (dst) dst->m_balance += amt;

    // הוספה ליומן של source (אם קיים)
    if (src)
    {
        Transaction** nextS = new Transaction * [src->m_numberOfTransaction + 1];
        for (int i = 0; i < src->m_numberOfTransaction; ++i)
            nextS[i] = new Transaction(*src->m_transactionList[i]);
        nextS[src->m_numberOfTransaction] = new Transaction(newTransaction);

        if (src->m_transactionList)
        {
            for (int i = 0; i < src->m_numberOfTransaction; ++i)
            {
                src->m_transactionList[i]->SetDate(NULL);
                delete src->m_transactionList[i];
            }
            delete[] src->m_transactionList;
        }
        src->m_transactionList = nextS;
        src->m_numberOfTransaction += 1;
    }

    // הוספה ליומן של destination (אם קיים)
    if (dst)
    {
        Transaction** nextD = new Transaction * [dst->m_numberOfTransaction + 1];
        for (int i = 0; i < dst->m_numberOfTransaction; ++i)
            nextD[i] = new Transaction(*dst->m_transactionList[i]);
        nextD[dst->m_numberOfTransaction] = new Transaction(newTransaction);

        if (dst->m_transactionList)
        {
            for (int i = 0; i < dst->m_numberOfTransaction; ++i)
            {
                dst->m_transactionList[i]->SetDate(NULL);
                delete dst->m_transactionList[i];
            }
            delete[] dst->m_transactionList;
        }
        dst->m_transactionList = nextD;
        dst->m_numberOfTransaction += 1;
    }
}