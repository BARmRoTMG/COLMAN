#ifndef SQUARE_H
#define SQUARE_H

#include "Quad.h"

class Square : public Quad
{
public:
	Square( double up = 0, double down = 0, double right = 0, double left = 0, const char* sn = "noName" );
								//constructor. center point = (0,0), name=sn
	virtual ~Square();			//destructor

public:
	void shiftX( int x );		//shifts the center of the square by x (right and left)
	void shiftY( int y );		//shifts the center of the square by y (up and down)
};

#endif