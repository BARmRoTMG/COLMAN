#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include <string.h>
#include <typeinfo>

class Shape
{
public:
	Shape( const char* sn = "noName" );					//Creates a new shape (name=sn,centerPoint = (0,0))
	Shape( const Shape& other );						//copy constructor of shape
	virtual ~Shape();									//shape destructor

public:
	void setName( const char* name );					//sets the shape's name
	void setCenter( const Point& p );					//sets the center point
	const char* getName() const;						//returns the shape's name
	Point getCenter() const;							//returns the center point
	void setShape( const char* sn, const Point& other );//set the shape's name and the center point
	static int numOfShapes();							//returnS the total number of shapes

public:
	const Shape& operator=( const Shape& other );		//operator=

public:
	virtual int calcArea() const = 0;					//returns the shape's area (rounded to int)
	virtual int calcPerimeter() const = 0;				//returns the shape's Perimeter (rounded to int)

protected:
	Point		m_centerPoint;

private:
	char*		m_shapeName;
	static int	s_totalNumOfShapes;
};

#endif