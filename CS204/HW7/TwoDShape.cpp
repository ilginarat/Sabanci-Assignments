#include "TwoDShape.h"
#include "Shape.h"
#include <string>
using namespace std;

TwoDShape::TwoDShape(string name):Shape(name)
{
}


TwoDShape::~TwoDShape(void)
{
}

float TwoDShape::volume() {
	myVolume=0;
	return myVolume;
}