#pragma once
#include <string>
#include "Shape.h"
using namespace std;

class TwoDShape :public Shape
{
public:
	TwoDShape(string name);
	~TwoDShape(void);
	virtual float volume();

protected:
	//I dont need to write myName, right?
	float myVolume;
};
