#pragma once

#include <string>
using namespace std;

class Shape
{
public:
	Shape(string name);
	~Shape(void);
	virtual float perimeter()=0;
	virtual float area()=0;
	virtual float volume()=0;
	string getName();

protected:
	 string myName;
};

