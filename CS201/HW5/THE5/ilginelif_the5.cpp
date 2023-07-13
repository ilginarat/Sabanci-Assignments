#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
#include "Reservation.h"
#include "date.h"
using namespace std;

Date sToD(string x) {
    int y = atoi(x.substr(0,4));
    int m = atoi(x.substr(5,2));
    int d = atoi(x.substr(8,2));
    return Date(m, d, y);
}


int main() {
	string reservation_file, boats_file, sailors_file, line1, line2, line3;
	ifstream input_reservation, input_boats, input_sailors;
	double r, a;
	string n, c, type, date, date2;
	int i, s_id, b_id;


	cout << "Enter filename for reservation database: ";
	cin >> reservation_file;
	input_reservation.open(reservation_file.c_str());

	if (input_reservation.fail()) {
		cout << "Cannot open the files. Exiting..." << endl << endl;
	}
	else {
		boats_file="Boats.txt";
		input_boats.open(boats_file.c_str());
		if (input_boats.fail()) {
			cout << "Cannot open the files. Exiting..." << endl;
		}
		else {
			sailors_file="Sailors.txt";
			input_sailors.open(sailors_file.c_str());

			if (input_sailors.fail()) {
				cout << "Cannot open the files. Exiting..." << endl;
			}
			else {
				vector<Boat> boat;
				getline(input_boats, line2);
				while(getline(input_boats, line2)) {
					istringstream boats(line2);
					boats >> i >> n >> c; 
					Boat b(i, n, c);
					boat.push_back(b);
				}

				vector<Sailor> sailor;
				getline(input_sailors, line3);
				while(getline(input_sailors, line3)) {
					istringstream sailors(line3);
					sailors >> i >> n >> r >> a;
					Sailor s(i, n, r, a);
					sailor.push_back(s);
				}

				Reservations a;

				
				while(getline(input_reservation, line1)) {
					Sailor wanted1;
					Boat wanted2;
					istringstream reservation(line1);
					reservation >> type >> s_id >> b_id >> date;
				
					if (type=="A") {
						
						for(unsigned int i=0; i<sailor.size(); i++) {
							if (s_id== sailor[i].Id()) 
							{
								wanted1=sailor[i];
							}
						}
						
						for(unsigned int i=0; i<boat.size(); i++) {
							
							if (b_id== boat[i].Id()) 
							{
								wanted2=boat[i];
								
							}
						}
						
						a.Add(wanted1, wanted2, date);
					}
					
					if (type=="D") {
						/*
						for(int i=0; i<sailor.size(); i++) {
							if (s_id== sailor[i].Id()) 
							{
								wanted1=sailor[i];
							}
						}
						

						for(int i=0; i<boat.size(); i++) {
							if (b_id == boat[i].Id()) 
							{
								wanted2=boat[i];
							}
						}
						*/
						if (a.Delete(s_id, b_id, date)) {
							   
							if (s_id==0) {
								cout << "Error: Could not delete reservation for boat id " << b_id << endl << endl;
							}
							else if (b_id==0) {
								cout << "Error: Could not delete reservation for sailor id " << s_id  << endl << endl;
							}
							else if (s_id!=0 && b_id!=0) {
								cout << "Error: Could not delete reservation \"" << s_id  << " "  << b_id << " "  << date << "\"" << endl << endl;
							}
    
						}
					}

					if (type=="F") {

						if (s_id ==0 && b_id==0) {
							reservation >> date2;
							if (a.FindDate(sToD(date), sToD(date2))) {
								 
								cout << "Error: No matching reservation found between dates " << date << " & " << date2 << endl << endl;

							}
						}
						if (s_id ==0 && b_id!=0) {
							a.FindBoatDate(b_id, date);
						}
						if (s_id !=0 && b_id==0) {
							a.FindSailorDate(s_id, date);
						}
					}
				}
			}
		}
	}
	return 0;
}