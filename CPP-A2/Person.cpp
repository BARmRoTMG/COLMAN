#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"

// Default
Person::Person()
{
    m_id = 0;
    m_name = nullptr;
}

// Parametric
Person::Person(const char* name, int id)
{
    m_id = id;
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

// Copy
Person::Person(const Person& other)
{
    m_id = other.m_id;
    if (other.m_name)
    {
        m_name = new char[strlen(other.m_name) + 1];
        strcpy(m_name, other.m_name);
    }
    else
    {
        m_name = nullptr;
    }
}

// Destructor
Person::~Person()
{
    delete[] m_name;
    m_name = nullptr;
}

void Person::SetName(const char* newName)
{
    if (newName == m_name) return;

    delete[] m_name;

    if (newName)
    {
        m_name = new char[strlen(newName) + 1];
        strcpy(m_name, newName);
    }
    else
    {
        m_name = nullptr;
    }
}

void Person::SetId(int newId)
{
    m_id = newId;
}

char* Person::GetName() const
{
    return m_name;
}

int Person::GetId() const
{
    return m_id;
}