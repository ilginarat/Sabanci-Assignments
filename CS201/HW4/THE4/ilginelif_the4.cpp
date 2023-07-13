#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
using namespace std;

struct details {

	string date, sailor_name, boat_name, color, rank, age, sailor_id, boat_id;
};

int convertDate(string date) {
	int calculateDate;
	date= date.substr(0,4)+date.substr(5,2)+date.substr(8,2);
	calculateDate=atoi(date);
	return calculateDate;
}

string StringtoDouble(string number) {
	int dot=number.find(".");
	if (number[dot+1] == '0') {
		string new_num= number.substr(0,dot);
		return new_num;
	}
	else {
		return number;
	}
}

int main() {
	string reservation_file, boats_file, sailors_file, line1, line2, line3;
	ifstream input_reservation, input_boats, input_sailors;
	details booking;

	cout << "Enter filename for reservation database: ";
	cin >> reservation_file;
	input_reservation.open(reservation_file.c_str());

	if (input_reservation.fail()) {
		cout << "Cannot open the files. Exiting..." << endl;
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
				vector<details> table;
				int i=0;
				getline(input_reservation, line1);
				while(getline(input_reservation, line1)) {
					istringstream reservation(line1);
					table.push_back(booking);
					reservation >> table[i].sailor_id >> table[i].boat_id >> table[i].date;
					getline(input_boats, line2);
					while(getline(input_boats, line2)) {
						istringstream boats(line2);
						vector<string> boat(3);
						boats >> boat[0] >> boat[1] >> boat[2];  
						if (table[i].boat_id == boat[0]) {
							table[i].boat_name=boat[1];
							table[i].color=boat[2];
						}
					}
					input_boats.clear();
					input_boats.seekg(0);
					
					getline(input_sailors, line3);
					while(getline(input_sailors, line3)) {
						istringstream sailors(line3);
						vector<string> sailor(4);
						sailors >> sailor[0] >> sailor[1] >> sailor[2] >> sailor[3];
						if (table[i].sailor_id == sailor[0]) {
							table[i].sailor_name=sailor[1];
							table[i].rank=sailor[2];
							table[i].age=sailor[3];
						}
					}
					input_sailors.clear();
					input_sailors.seekg(0);
					i++;
				}
				//sorting
				int min_index;
				int size= table.size();
				for (int x=0; x<size-1; x++) {
					int min=convertDate(table[x].date);
					min_index=x;
					for (int y=x+1; y<size; y++ ) {
						if (convertDate(table[y].date)== min) {
							bool x=true;
							int p=0;
							while (x) {
								if (table[y].sailor_name[p] < table[min_index].sailor_name[p] && p < table[y].sailor_name.length() && p < table[min_index].sailor_name.length() ) {  //should I add && p <= .length()
									min_index=y;
									x=false;
								}
								if (table[y].sailor_name[p] == table[min_index].sailor_name[p]) {
									p++;
								}
							}
						}
						if (convertDate(table[y].date)<min) {
							min=convertDate(table[y].date);
							min_index=y;
						}
					}
					details sth=table[min_index];
					table[min_index]=table[x];
					table[x]=sth;
				}
				//print
				for (int m=0; m<size; m++) {
					cout << table[m].date << " -> " << table[m].sailor_name << "(" << StringtoDouble(table[m].age) << "," << StringtoDouble(table[m].rank) << ") has reserved " << table[m].boat_name << "(" << table[m].color << ")" << endl;
				}
			}
		}
	}
	return 0;
}