#define _CRT_SECURE_NO_WARNINGS
#include "Survivor.h"


bool Survivor::Init(const char* _name, float _age, int _followers)
{
    if (!_name) return false;

    // חישוב אורך ידני
    size_t len = 0;
    while (_name[len] != '\0') ++len;

    // הקצאה (אם נכשלת תיזרק חריגה)
    char* buf = nullptr;
    try
    {
        buf = new char[len + 1];
    }
    catch (...)
    {
        return false;
    }

    // העתקה ידנית כולל '\0'
    for (size_t i = 0; i <= len; ++i)
        buf[i] = _name[i];

    // הצבה לשדות
    m_name = buf;
    m_age = _age;
    m_followers = _followers;
    return true;
}

Survivor* Survivor::Duplicate() const
{
    // הקצאת אובייקט חדש
    Survivor* dup = nullptr;
    try
    {
        dup = new Survivor();
    }
    catch (...)
    {
        return nullptr; // כשל בהקצאת האובייקט
    }

    // אתחול עם העתקה עמוקה לשם + שאר השדות
    const char* srcName = (m_name ? m_name : "");
    if (!dup->Init(srcName, m_age, m_followers))
    {
        delete dup;        // שחרור אם Init נכשל (למשל כשל בהקצאת שם)
        return nullptr;
    }

    return dup;
}

void Survivor::Free()
{
    if (m_name)
    {
        delete[] m_name;
        m_name = nullptr;
    }
    m_age = 0.0f;
    m_followers = 0;
}