#ifndef SURVIVOR_H
#define SURVIVOR_H


#include <string.h>

class Survivor
{
public:
	bool Init(const char* _name, float _age, int _followers);
	Survivor* Duplicate() const;
	void Free();

public://Do not touch this area - for testing
	Survivor() {}
	Survivor(char* _name, float _age, int _followers) : m_name(_name), m_age(_age), m_followers(_followers) {}
	const char* GetName() const { return m_name; }
	float GetAge() const { return m_age; }
	int GetFollowers() const { return m_followers; }
	void SetFollowers(int f) { m_followers = f; }
	void SetAge(float a) { m_age = a; }

private:
	char* m_name;			//the name of the survivor
	float	m_age;			//the age of the survivor
	int		m_followers;	//how many followers he has on social networks
};

#endif