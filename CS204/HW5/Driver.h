#include<iostream>
#include<string>
#include "Car.h"
using namespace std;

class Driver
{
public:
	Driver(Car &carName, double budget); 
	void drive (int & km);
	void repairCar(string type);
	void display();
	void fullFuel();

private:
	double myBudget;
	Car & myCar; //to make it shared
};

