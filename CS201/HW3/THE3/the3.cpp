#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
using namespace std;

void intoString(ifstream &input, string &keyString) {
	string line, word;
	int k=1;                                //which question
	while (getline(input, line)) {
		istringstream mystream(line);
		keyString+=tostring(k);
		k+=1;
		keyString+=",";
		while(mystream >> word) {
			keyString+=word;
			keyString+=",";
		}
	}
}

int main() {
	string filename, filename2, line, name, surname, word, house, keyString="";
	ifstream myfile, key;
	cout << "Hello and welcome to the Hogwarts house sorting hat program!" << endl;
	cout << "When I call your name, you'll come forth, I shall place the sorting hat on your head, and you will be sorted into your houses." << endl;
	cout << "Enter the name of the key file: ";
	cin >> filename2;
	key.open(filename2.c_str());
	while (key.fail()) {
		cout << "Error: Cannot open file " << filename2 << endl;
		cout << "Enter the name of the key file: ";
		cin >> filename2;
		key.open(filename2.c_str());
	}
	cout << "Enter the name of the answer file: ";
	cin >> filename;
	myfile.open(filename.c_str());
	while (myfile.fail()) {
		cout << "Error: Cannot open file " << filename << endl;
		cout << "Enter the name of the answer file: ";
		cin >> filename;
		myfile.open(filename.c_str());
	}	
	intoString(key, keyString);
	while(getline(myfile, line)) {
		if (line != "\r" && line != "") {
			istringstream input(line);
			input >> name >> surname;
			int point=0;
			int q=1;
			while (input >> word) {
				string question=tostring(q);
				int i=keyString.find(question);
				int f=keyString.find(word, i);
				string str=keyString.substr(i,f-i);
				int count=0;
				int index=0;
				while(str.find(",",index) != string::npos) {
					int ii=str.find(",",index);
					index=ii+1;
					count++;
				}
				point+=count;
				q++;
			}
			if (point < 10) {
				house = "Hufflepuff";
			}
			else if (point < 15) {
				house= "Ravenclaw";
			}
			else if (point < 21) {
				house="Gryffindor";
			}
			else {
				house="Slytherin";
			}
			cout << "Oh! we have " << name << " " << surname << " under the sorting hat. " << name << ", you scored " << point << " points, you are a " << house << "!" << endl;
		}
	}
	return 0;
}