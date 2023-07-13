#include <iostream>
#include <string>
using namespace std;

void getinput(string exercise, float &mins, float &reps, double &weightLifting) {

	if ( exercise != "Weight Lifting") {
	
		cout << exercise << ": ";
		cin >> mins >> reps;
	}
	
	if (exercise == "Weight Lifting") {

		cout << "Weight Lifting: ";
		cin >> mins >> reps >> weightLifting;
	}

}

bool inputCheck(float weight, float mins, float reps, double weightLifting) {

	bool x = true;
	
	if (weight < 30) {
		cout << "Weight out of range!" << endl;
		x=false;
	}
	
	else {
		if (weightLifting != 1.0) {
			
			if (weightLifting > 35 || 0 >= weightLifting) {
				cout << "Lifted weight out of range!" << endl;
				x=false;
			}

			else if (reps <0 || reps > 50) {
			cout << "Reps out of range!" << endl;
			x=false;
			}

			else if (mins < 0 || mins > 2000) {
			cout << "Minute out of range!" << endl;
			x=false;
			}
		}
		else {
		
			if (reps <0 || reps > 50) {
				cout << "Reps out of range!" << endl;
				x=false;
			}

			else if (mins < 0 || mins > 2000) {
				cout << "Minute out of range!" << endl;
				x=false;
			}
		}
	}
	return x;
}

void calculateMET(float reps, string exercise, double &MET) {

	if (exercise == "Lunges" ) {
		if(reps >= 30.0) MET=10.5;
		else if(reps >= 15.0) MET=6.5;
		else MET=3.0;
	}

	if (exercise == "Push Ups" ) {
		if(reps >= 15.0) MET=7.5;
		else MET=4.0;
	}

	if (exercise == "Pull Ups" ) {
		if(reps >= 25.0) MET=9.0;
		else MET=5.0;
	}
}

void calculateWeightLiftMET(float reps, double weightLifting, double &MET) {
	if (weightLifting >= 15.0) {
		if (reps >= 40) MET=13.5;
		else if (reps >= 20) MET=9.0;
		else MET=5.0;
	}
	else if (weightLifting >= 5.0) {
			if (reps >= 40) MET=12.0;
			else if (reps >= 20) MET=7.5;
			else MET=4.0;
	}
	else {
		if (reps >= 40.0) MET=10.0;
		else if (reps >= 20) MET=5.5;
		else MET=3.0;
	}
}

double minuteCalculation(double MET, double difference, float weight) {
	double minute= difference*200/(MET*3.5*weight);
	return minute;
}

void displayResults(double METL,double METPUSH,double METPULL,double METLIFT,double burnedL,double burnedPush,double burnedPull,double burnedLift,double totalburned, double difference, float weight) {

	cout << "From lunges, you burned " << burnedL << " calories." << endl;
	cout << "From push ups, you burned " << burnedPush << " calories." << endl;
	cout << "From pull ups, you burned " << burnedPull << " calories." << endl;
	cout << "From weight lifting, you burned " << burnedLift << " calories." << endl;
	cout << "You burned " << totalburned << " calories." << endl;
	cout << endl;

	if (difference > 0) {
		cout << "You did not reach your goal by "<< difference <<" calories." << endl;

		double minL = minuteCalculation(METL, difference, weight);
		double minPush = minuteCalculation(METPUSH, difference, weight);
		double minPull = minuteCalculation(METPULL, difference, weight);
		double minLift = minuteCalculation(METLIFT, difference, weight);

		cout << "You need to do lunges " << minL << " minutes more to reach your goal or," << endl;
		cout << "You need to do push ups " << minPush << " minutes more to reach your goal or," << endl;
		cout << "You need to do pull ups " << minPull << " minutes more to reach your goal or," << endl;
		cout << "You need to do weight lifting " << minLift << " minutes more to reach your goal." << endl;
	}
	if (difference == 0) {
		cout << "Congratulations! You have reached your goal!" << endl;
	}
	if (difference < 0) {
		difference = -difference;
		cout << "You have surpassed your goal! You can eat something worth " << difference << " calories :)" << endl;
	}
}

void computeresults(float weight, double goal, float repsL,float repsPush,float repsPull,float repsLift, double weightLifting, float minsPush,float minsPull, float minsL, float minsLift) {
	
	double METL, METPUSH, METPULL, METLIFT;

	calculateMET(repsL, "Lunges", METL);
	double burnedL = (minsL*(METL*3.5*weight))/200;

	calculateMET(repsPush, "Push Ups", METPUSH);
	double burnedPush = (minsPush*(METPUSH*3.5*weight))/200;

	calculateMET(repsPull, "Pull Ups", METPULL);
	double burnedPull = (minsPull*(METPULL*3.5*weight))/200;

	calculateWeightLiftMET(repsLift, weightLifting, METLIFT);
	double burnedLift = (minsLift*(METLIFT*3.5*weight))/200;

	double totalburned= burnedL+burnedPush+burnedPull+burnedLift;
	double difference=goal-totalburned;

	displayResults( METL, METPUSH, METPULL, METLIFT, burnedL, burnedPush, burnedPull, burnedLift, totalburned, difference, weight);

}

int main() {

	string name;
	float weight, minsL, repsL, minsPush, repsPush, minsPull, repsPull, minsLift, repsLift;
	double weightLifting, goal;

	weightLifting = 0;

	cout << "Please enter your name: ";
	cin >> name;
	cout << "Welcome " << name << ", please enter your weight(kg): ";
	cin >> weight;
	
	cout << name << ", please enter minutes and repetitions in a week for the activities below." << endl;

	getinput("Lunges", minsL, repsL, weightLifting);
	getinput("Push Ups", minsPush, repsPush, weightLifting);
	getinput("Pull Ups", minsPull, repsPull, weightLifting);

	cout << name << ", please enter minutes, repetitions and lifted weight in a week for the activities below." << endl;
	getinput("Weight Lifting", minsLift, repsLift, weightLifting);
	
	cout << name << ", please enter your weekly calorie burn goal: ";
	cin >> goal;

	if (inputCheck(weight, minsL, repsL, 1)) {
		if (inputCheck(weight, minsPush, repsPush, 1)) {
			if (inputCheck(weight, minsPull, repsPull, 1)) {
				if (inputCheck(weight, minsLift, repsLift, weightLifting)) {
					computeresults( weight,  goal, repsL, repsPush, repsPull, repsLift, weightLifting, minsPush, minsPull, minsL, minsLift);
				}
			}
		}
	}
	return 0;
}