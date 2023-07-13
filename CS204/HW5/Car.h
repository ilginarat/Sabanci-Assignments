#ifndef Car_h
#define Car_h

#include<iostream>
#include<string>

using namespace std;

class Car 
{
public:
	Car();
	Car (int fuel, int fee, int distance);
	void display();
	void distance(int& km);
	void fuel(double& f);
	void fee(int f);
	void Fullfuel();
	double displayFuel();
	double displayFee();
	double displayMaxFuel();
private:

	double myFuel; 
	int myDistance;
	double myFee;
	double maxFuel;
};
#endif