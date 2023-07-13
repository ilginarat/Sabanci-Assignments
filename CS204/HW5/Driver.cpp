#include "Driver.h"
#include<iostream>
#include<string>

using namespace std;

Driver::Driver(Car &carName, double budget) 
	:myCar(carName), myBudget(budget) //no copy here
{
}

void Driver::repairCar(string type) {

	if (type=="SMALL") {
		myBudget-=50;
		myCar.fee(5);
		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl << "Yearly insurance fee is increased to " << myCar.displayFee() <<" because of the SMALL accident";
	}
	else if (type=="MEDIUM") {
		myBudget-=150;
		myCar.fee(10);
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl << "Yearly insurance fee is increased to " << myCar.displayFee() <<" because of the MEDIUM accident";
	}
	else if (type=="LARGE") {
		myBudget-=300;
		myCar.fee(20);
		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl << "Yearly insurance fee is increased to " << myCar.displayFee() <<" because of the LARGE accident";
	}
}

void Driver::drive(int& km) {

	double fuelMoney=0.25*km;

	myCar.distance(km);
	myCar.fuel(fuelMoney);
}

void Driver::display() {
	cout << "Driver Budget: " << myBudget;
}

void Driver::fullFuel() {
	
	myBudget=myBudget-(myCar.displayMaxFuel()-myCar.displayFuel());
	myCar.Fullfuel();
	cout << "Fuel is full" << endl;
}