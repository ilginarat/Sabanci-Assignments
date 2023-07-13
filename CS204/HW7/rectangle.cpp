#include "rectangle.h"


rectangle::rectangle(string n, float w, float l)
	:TwoDShape(n), myWidth(w), myLength(l) //okey mi yani???
{
}


rectangle::~rectangle(void)
{
}

float rectangle::area() {
	myArea= myWidth*myLength;
	return myArea;
}

float rectangle::perimeter() {
	myPerimeter= 2*myWidth+2*myLength;
	return myPerimeter;
}