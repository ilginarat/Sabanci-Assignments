#include "Box.h"


Box::Box(string n,float w,float l,float h)                     //I do not think I can use polymorphism in these cases
	:ThreeDShape(n), myWidth(w), myLength(l), myHeight(h)
{
}


Box::~Box(void)
{
}


float Box::area() {
	myArea=2*(myWidth*myLength+myWidth*myHeight+myLength*myHeight);
	return myArea;
}

float Box::volume() {
	myVolume=myWidth*myLength*myHeight;
	return myVolume;
}