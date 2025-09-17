#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle( double r = 1, const char* sn = "noName" );		//create a circle with radius=1, name=sn and center=(0,0)
	Circle( const Circle& other );							//copy constructor
	virtual ~Circle();										//destructor

public:
	double getRadius() const;								//returns the circle's radius
	void setRadius( double r );								//set the radius

public:
	virtual int calcArea() const;							//returns the circle's area (rounded to int)
	virtual int calcPerimeter() const;						//returns the circle's Perimeter (rounded to int)

public:
	friend Circle operator+( int r, const Circle& other );	//returns a new Circle with added radius
	const Circle& operator=( const Circle& other );			//operator= that copies all
	const Circle& operator=( const char* name );			//updates only the name of the shape and returns the updated shape

private:
	double m_radius;
};

#endif