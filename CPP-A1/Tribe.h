#ifndef TRIBE_H
#define TRIBE_H


#include "Survivor.h"

class Tribe
{
public:
	bool Init(const char* name, const char* color);
	bool AddSurvivor(Survivor* s);
	Tribe* Duplicate() const;
	void SortByAge();
	void SortByName();
	int TotalFollowers() const;
	bool UpdateFollowers(const char* name, int toAdd);
	bool UpdateAge(const char* name, float newAge);
	int GetSurvivorFollowers(const char* name) const;
	void Free();

public: //Do not touch this area - for testing
	Tribe() {}
	Tribe(Survivor** survivors, int num_of_survivors, char* name, char* color) : m_survivors(survivors), m_num_of_survivors(num_of_survivors), m_name(name), m_bandana_color(color) {}
	Survivor** GetSurvivors() { return m_survivors; }
	int GetNumSurvivors() const { return m_num_of_survivors; }
	const char* GetName() const { return m_name; }
	const char* GetColor() const { return m_bandana_color; }

private:
	Survivor** m_survivors;		//a pointer to an array of pointers to survivors
	int			m_num_of_survivors;	//the number of survivors in the tribe
	char* m_name;				//the name of the tribe
	char* m_bandana_color;	//the color of the tribe's bandana
};

#endif