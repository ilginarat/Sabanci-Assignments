#pragma once
#include "ThreeDShape.h"
class Box : public ThreeDShape
{
public:
	Box(string n,float w,float l,float h);
	~Box(void);
	virtual float area();
	virtual float volume();

protected: 
	float myWidth;
	float myLength;
	float myHeight;
	float myVolume;
	float myArea;
};

