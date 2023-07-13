#pragma once
#include "shape.h"
class ThreeDShape : public Shape
{
public:
	ThreeDShape(string n);
	~ThreeDShape(void);
	virtual float perimeter();
protected:
	float myPerimeter;
};

