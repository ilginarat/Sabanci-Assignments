#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include "strutils.h"
using namespace std;

void choice1(int row, int col, vector<vector<char>> toDisplay, vector<vector<char>> toPlay) {   //to display the surroundings

	int row1, col1;

	cout << "Give the coordinates: ";
	cin >> row1 >> col1;

	while (!(row1>=0 && row1<row && col1>=0 && col1<col)) {
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> row1 >>col1;
	}

	toPlay[row1][col1]=toDisplay[row1][col1];

	cout << "Displaying the surrounding of (" << row1 <<"," << col1 << "):" <<endl;
	cout <<endl;

	for (int j=0; j<toPlay.size(); j++) {
		for (int k=0; k<toPlay[0].size(); k++) {
			cout << toPlay[j][k] << "   ";
		}
		cout << endl;
	}

	cout <<endl;
	cout << "Around (" << row1 << "," << col1 << ") you have "<< toDisplay[row1][col1] <<" bomb(s)" <<endl;
}

void choice2(int row, int col, vector<vector<char>> Bombs, bool &keepGoing, vector<vector<char>> toDisplay, vector<vector<char>> &toPlay, vector<vector<char>> Arrangment) {
	int row2, col2;      //to open the cell

	cout << "Give the coordinates: ";
	cin >> row2 >> col2;

	while (!(row2>=0 && row2<row && col2>=0 && col2<col)) {
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> row2 >>col2;
	}
	cout << "Opening cell (" << row2 <<"," << col2 <<"):" << endl;
	cout << endl;

	if(Bombs[row2][col2]=='B') {
		keepGoing=false;
		
		toPlay[row2][col2]=Bombs[row2][col2];
		for (int j=0; j<toPlay.size(); j++) {
			for (int k=0; k<toPlay[0].size(); k++) {
				cout << toPlay[j][k] << "   ";
			}
			cout << endl;
		}

		cout << "Unfortunately, you stepped on a mine" << endl;
		cout << endl;

		cout << "Arrangement of mines: " << endl;

		for (int a=0; a<Arrangment.size(); a++) {
			for (int b=0; b<Arrangment[0].size(); b++) {
				cout << Arrangment[a][b] << "   ";
			}
		cout << endl;
		}

		cout << ">>>>> Game Over! <<<<<";
	}

	else {
		toPlay[row2][col2]=toDisplay[row2][col2];

		for (int j=0; j<toPlay.size(); j++) {
			for (int k=0; k<toPlay[0].size(); k++) {
				cout << toPlay[j][k] << "   ";
			}
			cout << endl;
		}
	}
}

int main () {

	int col, row, nrMines;

	cout << "Give the dimensions of the matrix: ";
	cin >> row >> col;

	cout << "How many bombs: ";
	cin >> nrMines;

	while (nrMines > row*col-1 || nrMines <1 ) {
		
		if (nrMines > row*col-1) {
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: " <<endl;
		}
		if (nrMines <1) {
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: " <<endl;
		}
		cin >> nrMines;
	}

	vector<vector<char>> toDisplay (row, vector<char>(col, '0'));  //keeps the number of bombs in surrounding cells
	vector<vector<char>> toPlay (row, vector<char>(col, 'X'));     // the matrix you see while playing
	vector<vector<char>> Bombs (row, vector<char>(col, '0'));      //keeps the places of the bombs
	vector<vector<char>> Arrangment (row, vector<char>(col, 'X')); //arrangement of bombs (same with toDisplay but you see B if there is a bomb in that cell)

	int counter=0;
	vector <string> selectedOnes; // keeps the coordinates of the bombs

	while (counter != nrMines) {
		RandGen selected;

		int a=selected.RandInt(row*col); //randomly assigns coordinates between 0 and row*col-1
		string stringSelected=itoa(a);

		if (!count(selectedOnes.begin(), selectedOnes.end(), stringSelected)) {   //checks if the coordinated has already assigned before
			selectedOnes.push_back(stringSelected);
			counter++;
		}
	}
	
	/*
	for (int i=0; i<selectedOnes.size(); i++) {
		cout << selectedOnes[i] << endl;
	}
	we have the coordinates of our bombs so far
	*/

	for (unsigned int i=0; i<selectedOnes.size(); i++) {

		int iBombCoord= atoi(selectedOnes[i]);
		int whichRow=iBombCoord/col;             //turns the coordinates into columns and rows
		int whichCol=iBombCoord%col;

		Bombs[whichRow][whichCol]='B';

        //for each bomb following lines visit the surrounding cells and the place of bomb, increments the toDisplay value by one if it is not the place of bomb
		for (int myRow=whichRow-1; myRow <=whichRow+1; myRow++) {
			if (myRow >=0 && myRow<= row-1) { //controls if that row exists
				for (int myCol=whichCol-1; myCol <=whichCol+1; myCol++) {
					if (myCol >=0 && myCol<= col-1) { //controls if that column exists
						if (!(myRow==whichRow && myCol==whichCol)) {  

							int toInt=(int)toDisplay[myRow][myCol];
							toInt++;

							toDisplay[myRow][myCol]= (char)toInt; //increment by one
						}
					}
				}
			}
		}
	}
	/*
	for (int j=0; j<toDisplay.size(); j++) {
		for (int k=0; k<toDisplay[0].size(); k++) {
			cout << toDisplay[j][k] << "   ";
		}
		cout << endl;
	}
	//assigning the bombs is succesfull
		cout << endl;

	for (unsigned int m=0; m < Bombs.size(); m++) {
		for (unsigned int n=0; n < Bombs[0].size(); n++) {
			cout << Bombs[m][n] << "   ";
		}
		cout << endl;
	}
	*/

	Arrangment=toDisplay;
	
	for (unsigned int m=0; m < Bombs.size(); m++) {
		for (unsigned int n=0; n < Bombs[0].size(); n++) {
			if (Bombs[m][n]=='B') {
				Arrangment[m][n]=Bombs[m][n];
			}
		}
	}
	/*
	cout << endl;
	for (unsigned int p=0; p < Arrangment.size(); p++) {
		for (unsigned int r=0; r < Arrangment[0].size(); r++) {
			cout << Arrangment[p][r] << "   ";
		}
		cout << endl;
	}
	*/
	for (unsigned int t=0; t < toPlay.size(); t++) {            //sakin silme bunu
		for (unsigned int l=0; l < toPlay[0].size(); l++) {
			cout << toPlay[t][l] << "   ";
		}
		cout << endl;
	}
	
	bool keepGoing=true;

	while (keepGoing) {  

		bool didUserWin=true;

		for (unsigned int m=0; m < toPlay.size(); m++) {
			for (unsigned int n=0; n < toPlay[0].size(); n++) {
				if (toPlay[m][n]=='X') {
					if (Bombs[m][n]!='B') {  //if you see X on played matrix and that coordinates doesnt indicate B on bombs matrix, you didnt win
						didUserWin=false;
					}
				}
			}
		}

		if (didUserWin) {    //if you won the game

			cout << "Congratulations! All the non-mined cells opened successfully" <<endl;
			cout << "You won!" <<endl;
			cout << ">>>>> Game Over! <<<<<" <<endl;
			keepGoing=false;
			break;
		}

		cout << "Press:" << endl;
		cout << "1. If you want to find out the surrounding of a cell" << endl;
		cout << "2. If you want to open the cell" << endl;
		cout << "3. If you want to exit." << endl;

		string answer;
		cin >> answer;

		while (!(answer =="1" ||answer =="2" ||answer =="3")) {
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl; 
			cin >> answer;
		}

		if (answer=="1") {
			choice1(row, col, toDisplay, toPlay);
		}

		else if (answer=="2") {
			choice2(row, col, Bombs, keepGoing, toDisplay, toPlay, Arrangment);
		}

		else if (answer=="3") {
			keepGoing=false;
			cout << "Program exiting ...";
		}
	}
	return 0;
}