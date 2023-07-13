#include <iostream>
#include <string>
using namespace std;


void getinput(string name, string exercise, float &mins, float &reps, double &weightLifting) {

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

void computeresults(string name, float weight, double goal, float repsL,float repsPush,float repsPull,float repsLift, double weightLifting, float minsPush,float minsPull, float minsL, float minsLift, double &METL, double &METPUSH,double &METPULL,double &METLIFT, double &burnedL, double &burnedPush, double &burnedPull, double &burnedLift, double &totalburned, double &difference) {
	// ý should't have used mets as reference parameters but dont ý have to??
	calculateMET(repsL, "Lunges", METL);
	burnedL = (minsL*(METL*3.5*weight))/200;

	calculateMET(repsPush, "Push Ups", METPUSH);
	burnedPush = (minsPush*(METPUSH*3.5*weight))/200;

	calculateMET(repsPull, "Pull Ups", METPULL);
	burnedPull = (minsPull*(METPULL*3.5*weight))/200;

	calculateWeightLiftMET(repsLift, weightLifting, METLIFT);
	burnedLift = (minsLift*(METLIFT*3.5*weight))/200;

	totalburned= burnedL+burnedPush+burnedPull+burnedLift;
	difference=goal-totalburned;
}

double minuteCalculation(double MET, double difference, float weight) {
	double minute= difference*200/(MET*3.5*weight);
	return minute;
}

void displayResults(double METL,double METPUSH,double METPULL,double METLIFT,double burnedL,double burnedPush,double burnedPull,double burnedLift,double totalburned, double difference, float weight, double goal) {

	cout << "From lunges, you burned " << burnedL << " calories." << endl;
	cout << "From push ups, you burned " << burnedPush << " calories." << endl;
	cout << "From pull ups, you burned " << burnedPull << " calories." << endl;
	cout << "From weight lifting, you burned " << burnedLift << " calories." << endl;
	cout << "You burned " << totalburned << " calories." << endl;
	cout << endl;

	if (goal > totalburned) {
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
	if (goal == totalburned) {
		cout << "Congratulations! You have reached your goal!" << endl;
	}
	if (goal < totalburned) {
		difference = -difference;
		cout << "You have surpassed your goal! You can eat something worth " << difference << " calories :)" << endl;
	}
}

int main() {

	string name;
	float weight, minsL, repsL, minsPush, repsPush, minsPull, repsPull, minsLift, repsLift;
	double METL, METPUSH, METPULL, METLIFT, weightLifting, burnedL, burnedPush, burnedPull, burnedLift, totalburned, difference, goal;

	weightLifting = 1.0;

	cout << "Please enter your name: ";
	cin >> name;
	cout << "Welcome " << name << ", please enter your weight(kg): ";
	cin >> weight;
	
	cout << name << ", please enter minutes and repetitions in a week for the activities below." << endl;

	getinput(name, "Lunges", minsL, repsL, weightLifting);
	getinput(name, "Push Ups", minsPush, repsPush, weightLifting);
	getinput(name, "Pull Ups", minsPull, repsPull, weightLifting);

	cout << name << ", please enter minutes, repetitions and lifted weight in a week for the activities below." << endl;
	getinput(name, "Weight Lifting", minsLift, repsLift, weightLifting);
	
	cout << name << ", please enter your weekly calorie burn goal: ";
	cin >> goal;

	bool a = inputCheck(weight, minsL, repsL, weightLifting);
	bool b = inputCheck(weight, minsPush, repsPush, weightLifting);
	bool c = inputCheck(weight, minsPull, repsPull, weightLifting);
	bool d = inputCheck(weight, minsLift, repsLift, weightLifting);


	if (a) {
		if (b) {
			if (c) {
				if (d) {
					computeresults( name,  weight,  goal, repsL, repsPush, repsPull, repsLift, weightLifting, minsPush, minsPull, minsL, minsLift, METL, METPUSH, METPULL, METLIFT, burnedL, burnedPush, burnedPull, burnedLift, totalburned, difference);
					displayResults( METL, METPUSH, METPULL, METLIFT, burnedL, burnedPush, burnedPull, burnedLift, totalburned, difference, weight, goal);
				}
			}
		}
	}
	return 0;
}