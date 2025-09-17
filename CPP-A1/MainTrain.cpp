#include <iostream> 
#include "Tribe.h"

using namespace std;

bool compareSurvivorDifferentAddress(Survivor* s1, Survivor* s2)
{
    if (s1 == s2 || s1 == nullptr || s2 == nullptr)
        return false;

    if (s1->GetName() == s2->GetName())
        return false;

    if (strcmp(s1->GetName(), s2->GetName()) != 0)
        return false;

    if (s1->GetAge() != s2->GetAge())
        return false;

    if (s1->GetFollowers() != s2->GetFollowers())
        return false;

    return true;
}

bool compareTribeDifferentAddress(Tribe* t1, Tribe* t2)
{
    if (t1 == t2 || t1 == nullptr || t2 == nullptr)
        return false;

    if (t1->GetName() == t2->GetName())
        return false;

    if (strcmp(t1->GetName(), t2->GetName()) != 0)
        return false;

    if (t1->GetColor() == t2->GetColor())
        return false;

    if (strcmp(t1->GetColor(), t2->GetColor()) != 0)
        return false;

    if (t1->GetNumSurvivors() != t2->GetNumSurvivors())
        return false;

    if (t1->GetSurvivors() == t2->GetSurvivors() && t1->GetSurvivors() != nullptr)
        return false;

    for (int i = 0; i < t1->GetNumSurvivors(); ++i)
    {
        if (false == compareSurvivorDifferentAddress(t1->GetSurvivors()[i], t2->GetSurvivors()[i]))
            return false;
    }

    return true;
}

bool checkSurvivor(Tribe* t, Survivor* s)
{
    if (nullptr == t || nullptr == s)
        return false;

    for (int i = 0; i < t->GetNumSurvivors(); ++i)
    {
        if (0 == strcmp(t->GetSurvivors()[i]->GetName(), s->GetName())
            && t->GetSurvivors()[i]->GetAge() == s->GetAge()
            && t->GetSurvivors()[i]->GetFollowers() == s->GetFollowers())
            return true;
    }

    return false;
}

bool checkSortedByAgesArray(Tribe* t, float ages[])
{
    for (int i = 0; i < t->GetNumSurvivors(); ++i)
    {
        if (t->GetSurvivors()[i]->GetAge() != ages[i])
            return false;
    }

    return true;
}

int main()
{
    float age1 = 26.f, age2 = 56.f, age3 = 21.5f, age4 = 38.5f;
    float arr1[] = { age3, age1, age4, age2 };
    float arr2[] = { age3, age2, age4, age1 };
    char name1[] = "Moshe Moshkovitz";
    char name2[] = "David Davidian";
    char name3[] = "Azzam Azzam";
    char name4[] = "Eli Eliyahu";
    char tName1[] = "Colman";
    char tName2[] = "Sunrise";
    char tName3[] = "Sunset";
    char color1[] = "Red";
    char color2[] = "Blue";
    char color3[] = "Orange";
    Survivor s1 = { name1, age1, 30 };
    Survivor s2 = { name2, age2, 25 };
    Survivor s3 = { name3, age3, 32 };
    Survivor s4 = { name4, age4, 20 };
    Survivor* pItem[3] = { &s1, &s2, &s3 };
    Survivor* pItem2[4] = { &s1, &s2, &s3, &s4 };
    Tribe t0 = { nullptr, 0, tName1, color1 };
    Tribe t = { pItem, 3, tName2, color2 };
    Tribe t2 = { pItem2, 4, tName3, color3 };
    Tribe tmpTribe;
    Tribe* myTribe;
    Survivor p1;
    Survivor* p2;

    //------------------------------------------------------------------------------------------------------------
    //=============== EX 1 ================// 
    p1.Init(name1, age1, 30);
    if (false == compareSurvivorDifferentAddress(&p1, &s1))
        cout << "Failed Ex1 - CreateNewSurvivor function (-8)\n";

    //=============== EX 2 ================// 
    p2 = s2.Duplicate();
    if (false == compareSurvivorDifferentAddress(p2, &s2))
        cout << "Failed Ex2 - DuplicateSurvivor function (-8)\n";

    //=============== EX 3 ================// 
    tmpTribe.Init(tName1, color1);
    if (false == compareTribeDifferentAddress(&tmpTribe, &t0))
        cout << "Failed Ex3 - Init function (-8)\n";

    //=============== EX 4 ================// 
    tmpTribe.AddSurvivor(&s1);
    if (false == checkSurvivor(&tmpTribe, &s1))
        cout << "Failed Ex3 - AddSurvivor function (-8)\n";

    //=============== EX 5 ================// 
    myTribe = t.Duplicate();
    if (false == compareTribeDifferentAddress(&t, myTribe))
        cout << "Failed Ex5 - DuplicateTribe function (-8)\n";

    //=============== EX 6 ================// 
    t2.SortByAge();
    if (false == checkSortedByAgesArray(&t2, arr1))
        cout << "Failed Ex6 - SortByAge function (-8)\n";

    //=============== EX 7 ================// 
    t2.SortByName();
    if (false == checkSortedByAgesArray(&t2, arr2))
        cout << "Failed Ex7 - SortByName function (-8)\n";

    //=============== EX 8 ================// 
    if (t2.TotalFollowers() != 107)
        cout << "Failed Ex8 - TotalFollowers function (-8)\n";

    //=============== EX 9 ================// 
    if (false == t2.UpdateFollowers(name3, 10))
        cout << "Failed Ex9 - UpdateFollowers function (-8)\n";
    else if (t2.GetSurvivors()[0]->GetFollowers() != 42)
        cout << "Failed Ex9 - UpdateFollowers function (-8)\n";

    //=============== EX 10 ================// 
    if (0 != t2.UpdateAge("lala", 4.5))
        cout << "Failed Ex10 - UpdateAge function (-8)\n";

    //=============== EX 11 ================// 
    if (20 != t2.GetSurvivorFollowers(name4))
        cout << "Failed Ex11 - GetSurvivorFollowers function (-8)\n";

    //=============== EX 12+13 ================// 
    myTribe->Free();

    //=============== FINISH ================// 
    cout << "done\n";

    return 0;
}