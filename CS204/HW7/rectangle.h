#pragma once
#include <string>         //habire string eklememeli miyim?
#include "TwoDShape.h"
using namespace std;

class rectangle : public TwoDShape
{
public:
	rectangle(string n, float w, float l);
	~rectangle(void);
	virtual float area();
	virtual float perimeter();

protected:
	float myArea;
	float myPerimeter;
	float myWidth;
	float myLength;
};

//since there is no overriding, I dont need to write volume() again, right?