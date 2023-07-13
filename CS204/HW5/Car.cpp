#include<iostream>
#include<string>
#include"Car.h"
using namespace std;

Car::Car() {
}

Car::Car(int fuel, int fee, int distance) {
	myFuel=fuel;
	myFee=fee;
	myDistance=distance;
	maxFuel=fuel;
}

void Car::distance (int & km) { //is & needed?

	myDistance+=km;
}

void Car::fuel (double & f) { //is & needed?

	myFuel-=f;
}
void Car::fee (int f) {
	double ratio=(100+f)/100.0;
	double newFee=ratio*myFee;
	myFee=newFee;
}

void Car::Fullfuel() {
	myFuel=maxFuel;
}

void Car::display() {
	cout << "Fuel Level: " << myFuel << endl << "Insurance Fee: " << myFee << endl << "Total distance that the car has travelled: " << myDistance << endl;
}

double Car::displayFuel() {
	return myFuel;
}

double Car::displayFee() {
	return myFee;
}

double Car::displayMaxFuel() {
	return maxFuel;
}