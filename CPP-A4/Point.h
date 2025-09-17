#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

const double PI = 3.14159;

class Point
{
public:
	Point( int x = 0, int y = 0 );
	Point( const Point& other );
	~Point();

public:
	int getX() const;										//returns the x
	int getY() const;										//returns the y
	void setX( int x );										//sets the x
	void setY( int y );										//sets the y
	void setPoint( int x, int y );							//sets the x and y
	void setPoint( const Point & other );					//sets the point with other values

public:
	bool operator==( const Point& other ) const;			//returns true if and only if the two points are equal
	bool operator!=( const Point& other ) const;			//returns true if and only if the two points are not equal
	Point operator+( int num ) const;						//returns a new point with updated x(x+num) and y(y+num)
	const Point& operator+=( int num );						//updates the point with x(x+num) and y(y+num) and returns the updated point
	operator int() const;									//returns the sum of x and y
	Point operator+( const Point& other ) const;			//adds coordinates (x,y) and returns a new point
	Point operator++( int );								//adds 1 to x and y and returns the updated point - postfix
	const Point& operator++();								//adds 1 to x and y and returns the updated point - prefix
	friend Point operator*( int num, const Point& other );	//returns a new point with (x,y)*num

private:
	int m_x;
	int m_y;
};

#endif