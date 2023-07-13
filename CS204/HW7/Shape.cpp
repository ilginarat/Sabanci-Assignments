#include "Shape.h"


Shape::Shape(string name)
	:myName(name)
{
}


Shape::~Shape(void)
{
}

string Shape::getName() {
	return myName;
}

//member func olarak parameter, area, volume eklemiyoruz dimi?