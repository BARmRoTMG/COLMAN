#include "allShapes.h"
#include "Circle.h"
#include "Square.h"

//Train
int main()
{
	allShapes shapes;

	Circle * c1 = new Circle( 3, "myCircle" );
	Circle * c2 = new Circle( 2, "yourCircle" );

	Square * s1 = new Square( 1, 1, 1, 1, "mySquare" );
	Square * s2 = new Square( 2, 2, 2, 2, "yourSquare" );

	Quad * q1 = new Quad( 2, 2, 2, 2, "myQuad" );
	Quad * q2 = new Quad( 4, 3, 4, 3, "yourQuad" );

	if( Shape::numOfShapes() != 6 )
		cout << "Error with numOfShapes = 6 (-3)" << endl;


	shapes.addShape( c1 );
	shapes.addShape( c2 );
	shapes.addShape( s1 );
	shapes.addShape( s2 );
	shapes.addShape( q1 );
	shapes.addShape( q2 );

	if( shapes.totalArea() != 65 )
		cout << "Error with totalArea = 65 (-3)" << endl;

	if( shapes.totalPerimeter() != 64 )
		cout << "Error with totalPerimeter = 64 (-3)" << endl;

	if( shapes.totalCircleArea() != 40 )
		cout << "Error with totalCircleArea = 40 (-3)" << endl;

	if( shapes.totalSquarePerimeter() != 12 )
		cout << "Error with totalSquarePerimeter = 12 (-3)" << endl;

	shapes.removeShape( 4 );
	shapes.removeShape( 2 );
	shapes.removeShape( 0 );

	if( shapes.totalArea() != 32 )
		cout << "Error with totalArea = 32 (-3)" << endl;

	if( shapes.totalPerimeter() != 34 )
		cout << "Error with totalPerimeter = 34 (-3)" << endl;

	if( shapes.totalCircleArea() != 12 )
		cout << "Error with totalCircleArea = 19 (-3)" << endl;

	if( shapes.totalSquarePerimeter() != 8 )
		cout << "Error with totalSquarePerimeter = 8 (-3)" << endl;

	Point myPoint1( 1, 1 );
	Point myPoint2( 1, 1 );
	Point myPoint3( 2, 2 );
	Point myPoint4( 0, 0 );
	Point myPoint5;

	myPoint5 = myPoint4++;
	myPoint5 = ++myPoint4;

	if( myPoint1 != myPoint2 )
		cout << "Error with operator != in class point (-3)" << endl;

	if( myPoint3 == myPoint2 )
		cout << "Error with operator == in class point (-3)" << endl;

	myPoint1 = myPoint1 + 1;
	if( myPoint1.getX() != 2 || myPoint1.getY() != 2 )
		cout << "Error with operator +int in class point (-3)" << endl;

	myPoint1 += 1;
	if( myPoint1.getX() != 3 || myPoint1.getY() != 3 )
		cout << "Error with operator +=int in class point (-3)" << endl;

	myPoint4 = myPoint1 + myPoint3;
	if( myPoint4.getX() != 5 || myPoint4.getY() != 5 )
		cout << "Error with operator +point in class point (-3)" << endl;

	myPoint4++;
	if( myPoint4.getX() != 6 || myPoint4.getY() != 6 )
		cout << "Error with operator ++ in class point (-3)" << endl;

	int p = (int)myPoint4;
	if( p != 12 )
		cout << "Error with operator casting to int int class Point (-3)" << endl;

	myPoint4 = 3 * myPoint4;
	if( myPoint4.getX() != 18 || myPoint4.getY() != 18 )
		cout << "Error with operator * in class point (-3)" << endl;

	Circle myC1;
	const char* n = "myCircle!";
	myC1 = n;
	if( strcmp( myC1.getName(), n ) != 0  )
		cout << "Error with operator =const char* in class Shape (-3)" << endl;


	Quad * newQ = new Quad;
	shapes += newQ;

	if( shapes.getSize() != 4 )
		cout << "Error with operator+= in class allShapes (-3)" << endl;

	Shape * myShape1 = NULL;

	myShape1 = shapes[0];

	if( myShape1 == NULL )
		cout << "Error with operator[] in class allShapes (-3)" << endl;

	allShapes newAllShapes = shapes + shapes;
	if( newAllShapes.getSize() != 8 )
		cout << "Error with operator+allShapes in class allShapes (-3)" << endl;

	myC1 = 3 + myC1;
	if( myC1.getRadius() != 4 )
		cout << "Error with operator int+Circle in class Circle (-3)" << endl;

	int size = newAllShapes;
	if( size != 8 )
		cout << "Error with operator casting to int in class allShapes (-3)" << endl;


	cout << "done" << endl;

	return 0;
}

