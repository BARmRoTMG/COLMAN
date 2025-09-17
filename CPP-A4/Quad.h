#ifndef QUAD_H
#define QUAD_H

#include "Shape.h"

class Quad : public Shape
{
public:
	Quad( double up = 0, double down = 0, double right = 0, double left = 0, const char* sn = "noName" );
											//constructor. center point = (0,0), name=sn
	Quad( const Quad& other );				//copy constructr
	virtual ~Quad();						//destructor

public:
	virtual int calcArea() const;			//returns the quad's area (right*up) (rounded to int)
	virtual int calcPerimeter() const;		//returns the quad's Perimeter (the sum of the four ribs) (rounded to int)

private:
	double m_up;
	double m_down;
	double m_right;
	double m_left;
};

#endif