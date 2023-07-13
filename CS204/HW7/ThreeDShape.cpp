#include "ThreeDShape.h"


ThreeDShape::ThreeDShape(string n)
	:Shape(n)
{
}


ThreeDShape::~ThreeDShape(void)
{
}

float ThreeDShape::perimeter() {
	myPerimeter= 0;
	return myPerimeter;
}