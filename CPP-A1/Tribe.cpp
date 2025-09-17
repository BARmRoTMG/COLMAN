#include "Tribe.h"

bool Tribe::Init(const char* name, const char* color)
{
    // שבט מתחיל ריק
    m_survivors = nullptr;
    m_num_of_survivors = 0;

    // --- שם ---
    m_name = nullptr;
    if (name)
    {
        size_t n = 0;
        while (name[n] != '\0') ++n;

        char* tmp = nullptr;
        try { tmp = new char[n + 1]; }
        catch (...) { return false; }

        for (size_t i = 0; i <= n; ++i) tmp[i] = name[i];
        m_name = tmp;
    }

    // --- צבע ---
    m_bandana_color = nullptr;
    if (color)
    {
        size_t n = 0;
        while (color[n] != '\0') ++n;

        char* tmp = nullptr;
        try { tmp = new char[n + 1]; }
        catch (...)
        {
            if (m_name) { delete[] m_name; m_name = nullptr; }
            return false;
        }

        for (size_t i = 0; i <= n; ++i) tmp[i] = color[i];
        m_bandana_color = tmp;
    }

    return true;
}

bool Tribe::AddSurvivor(Survivor* s)
{
    if (!s) return false;

    // בדיקה אם כבר קיים שבט עם אותו שם
    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        if (strcmp(m_survivors[i]->GetName(), s->GetName()) == 0)
        {
            return false; // כבר קיים
        }
    }

    // שכפול השורד
    Survivor* copy = s->Duplicate();
    if (!copy) return false; // כשל בהקצאה

    // מערך חדש גדול באחד
    Survivor** newArr = nullptr;
    try
    {
        newArr = new Survivor * [m_num_of_survivors + 1];
    }
    catch (...)
    {
        copy->Free();
        delete copy;
        return false;
    }

    // העתקה של הישנים
    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        newArr[i] = m_survivors[i];
    }

    // הוספת החדש
    newArr[m_num_of_survivors] = copy;

    // שחרור המערך הישן
    if (m_survivors)
    {
        delete[] m_survivors;
    }

    // עדכון מצביעים וספירה
    m_survivors = newArr;
    ++m_num_of_survivors;

    return true;
}

Tribe* Tribe::Duplicate() const
{
    // הקצאת אובייקט חדש
    Tribe* dup = nullptr;
    try
    {
        dup = new Tribe();
    }
    catch (...)
    {
        return nullptr;
    }

    // העתקה עמוקה של שם וצבע + אתחול מערך השורדים לריק
    if (!dup->Init(m_name, m_bandana_color))
    {
        delete dup;
        return nullptr;
    }

    // שכפול כל השורדים (דרך AddSurvivor שמבצע Duplicate לכל Survivor)
    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        if (!dup->AddSurvivor(m_survivors[i]))
        {
            // כשל באמצע: משחררים הכל ומחזירים nullptr
            dup->Free();
            delete dup;
            return nullptr;
        }
    }

    return dup;
}

void Tribe::SortByAge()
{
    for (int i = 0; i < m_num_of_survivors - 1; ++i)
    {
        for (int j = i + 1; j < m_num_of_survivors; ++j)
        {
            if (m_survivors[j]->GetAge() < m_survivors[i]->GetAge())
            {
                // החלפת מצביעים
                Survivor* tmp = m_survivors[i];
                m_survivors[i] = m_survivors[j];
                m_survivors[j] = tmp;
            }
        }
    }
}

void Tribe::SortByName()
{
    for (int i = 0; i < m_num_of_survivors - 1; ++i)
    {
        for (int j = i + 1; j < m_num_of_survivors; ++j)
        {
            if (strcmp(m_survivors[j]->GetName(), m_survivors[i]->GetName()) < 0)
            {
                Survivor* tmp = m_survivors[i];
                m_survivors[i] = m_survivors[j];
                m_survivors[j] = tmp;
            }
        }
    }
}

int Tribe::TotalFollowers() const
{
    int sum = 0;
    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        if (m_survivors[i])
        {
            sum += m_survivors[i]->GetFollowers();
        }
    }
    return sum;
}

bool Tribe::UpdateFollowers(const char* name, int toAdd)
{
    if (!name) return false;

    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        if (strcmp(m_survivors[i]->GetName(), name) == 0)
        {
            m_survivors[i]->SetFollowers(m_survivors[i]->GetFollowers() + toAdd);
            return true;
        }
    }
    return false;
}

bool Tribe::UpdateAge(const char* name, float newAge)
{
    if (!name) return false;

    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        const char* curr = m_survivors[i]->GetName();

        // השוואה ידנית כמו strcmp
        int cmp = 0;
        size_t k = 0;
        while (curr[k] != '\0' && name[k] != '\0')
        {
            if (curr[k] < name[k]) { cmp = -1; break; }
            if (curr[k] > name[k]) { cmp = 1;  break; }
            ++k;
        }
        if (cmp == 0)
        {
            if (curr[k] == '\0' && name[k] != '\0') cmp = -1;
            else if (curr[k] != '\0' && name[k] == '\0') cmp = 1;
        }

        if (cmp == 0)
        {
            m_survivors[i]->SetAge(newAge);
            return true;
        }
    }
    return false;
}

int Tribe::GetSurvivorFollowers(const char* name) const
{
    if (!name) return -1;

    for (int i = 0; i < m_num_of_survivors; ++i)
    {
        const char* curr = m_survivors[i]->GetName();

        // השוואה ידנית כמו strcmp
        int cmp = 0;
        size_t k = 0;
        while (curr[k] != '\0' && name[k] != '\0')
        {
            if (curr[k] < name[k]) { cmp = -1; break; }
            if (curr[k] > name[k]) { cmp = 1;  break; }
            ++k;
        }
        if (cmp == 0)
        {
            if (curr[k] == '\0' && name[k] != '\0') cmp = -1;
            else if (curr[k] != '\0' && name[k] == '\0') cmp = 1;
        }

        if (cmp == 0)
        {
            return m_survivors[i]->GetFollowers();
        }
    }

    return -1; // לא נמצא
}

void Tribe::Free()
{
    // שחרור השורדים עצמם (אם נוצרו ב-Duplicate או AddSurvivor)
    if (m_survivors)
    {
        for (int i = 0; i < m_num_of_survivors; ++i)
        {
            if (m_survivors[i])
            {
                m_survivors[i]->Free();
                delete m_survivors[i];
            }
        }
        delete[] m_survivors;
        m_survivors = nullptr;
    }

    // שחרור השם
    if (m_name)
    {
        delete[] m_name;
        m_name = nullptr;
    }

    // שחרור הצבע
    if (m_bandana_color)
    {
        delete[] m_bandana_color;
        m_bandana_color = nullptr;
    }

    m_num_of_survivors = 0;
}