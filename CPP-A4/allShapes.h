#ifndef ALLSHAPES_H
#define ALLSHAPES_H

#include "Shape.h"

class allShapes
{
public:
	allShapes();							//constructor, zero elements
	allShapes( const allShapes& other );	//copy c'tor - deep copy
	~allShapes();							//destructor to all elements

public:
	int getSize() const;				//returns the number of shapes;

public:
	void addShape( Shape* newShape );	//add a new shape (deep copy) to the end of array
	void removeShape( int index );		//remove shape by index
	int totalArea() const;				//returns the total area of all the shapes (rounded to int)
	int totalPerimeter() const;			//returns the total Perimeter of all the shapes (rounded to int)
	int totalCircleArea() const;		//returns the total sum of circle areas (rounded to int)
	int totalSquarePerimeter() const;	//returns the total sum of squar Perimeter (rounded to int)

public:
	const allShapes& operator+=( Shape* newS );				//adds a new shape
	Shape* operator[]( int ind ) const;						//returns the shape located at index ind
	allShapes operator+( const allShapes& other ) const;	//returns a new allShape with all elements located at this and other
	operator int() const;									//returns the number of elements	

private:
	Shape** m_arr;
	int		m_size;
};

#endif