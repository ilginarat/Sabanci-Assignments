#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct busStop {
	string busStopName;
	busStop *left;
	busStop *right;

	busStop::busStop()
	{
		busStop *right=NULL; //okey mi?
		busStop *left=NULL;
	}
};
struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;

	busLine::busLine()
	{
		busLine *next=NULL;
	}
};

busLine* heaD = nullptr;

bool ifInLine(string x, busLine* y, busLine*& find) {
	if (y!=NULL) {
		if (x==y->busLineName) {
			find=y;
			return true;
		}
		else {
			while (y->next!=NULL) {
				if (x==y->next->busLineName) {
					find=y->next;
					return true;
				}
				y=y->next;
			}
			return false;
		}
	}
	else {
		return false;
	}
}

bool ifInStop(string x, busStop* y, busStop* &find) {
	if (y!=NULL) {
		if (x==y->busStopName) {
			find=y;
			return true;
		}
		else {
			while (y->right!=NULL) {
				if (x==y->right->busStopName) {
					find=y->right;
					return true;
				}
				y=y->right;
			}
			return false;
		}
	}
	else {
		return false;
	}
}

void printBusLines(busLine * busLineHead) {

	busLine * HeadOfLine=busLineHead;

	while (HeadOfLine!=NULL) {
		cout << HeadOfLine->busLineName <<": ";

		busStop* HeadOfStop=HeadOfLine->busStops->right;

		while (HeadOfStop->right!=NULL) {
			cout << HeadOfStop->left->busStopName << "<->";
			HeadOfStop=HeadOfStop->right;
		}
		cout << HeadOfStop->left->busStopName << "<->";
		cout << HeadOfStop->busStopName << endl;
		cout <<endl;
		HeadOfLine=HeadOfLine->next;
	}
}

void printMainMenu() {
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}

void addBusLine(busLine* &tail, busLine* &busLineHead) {

	string each, word, newBusLine, answer;
	cout << "Enter the name of the new bus line (0 for exit to main menu)."<<endl; 
	cin >> newBusLine;
	
	if (newBusLine!="0") {
		busLine* whereIs=NULL;
		while (ifInLine(newBusLine, busLineHead, whereIs)) { 
			cout << "Bus line already exists: enter a new one (0 for exit)" <<endl; 
			cin >> newBusLine;
		}

		if (newBusLine!="0") { //busline does not exist
			busLine* ptr=new busLine;
			ptr->next=NULL;
			ptr->busLineName=newBusLine;
			ptr->busStops=new busStop;
			cout <<"Enter the name of the next bus stop (enter 0 to complete)"; // for first stop
			cin >> word;
			if (word!="0") {
				busStop*head=ptr->busStops;
				head->busStopName=word;
				head->right=NULL;
				head->left=NULL;

				busStop* whereStop=NULL;

				cout <<"Enter the name of the next bus stop (enter 0 to complete)";
				cin >> word;
				while (word!="0") {
					if (ifInStop(word, head, whereStop)) {  
						cout << "Bus stop already exists in the line" <<endl;
					}
					else {
						busStop* ptr2= new busStop;
						ptr2->busStopName=word;
						ptr2->right=NULL;
						head->right=ptr2;
						ptr2->left=head;
						head=ptr2;
					}
					cout <<"Enter the name of the next bus stop (enter 0 to complete)";
					cin >> word;
				}
				cout <<"The bus line information is shown below"<< endl;
                
				cout << ptr->busLineName << ": " << ptr->busStops->busStopName;
				busStop* printHead=ptr->busStops;			
				while(printHead->right!=NULL) {
					cout << "<->" << printHead->right->busStopName;
					printHead=printHead->right;
				}
				cout << endl;

                cout <<"Are you sure? Enter (y/Y) for yes (n/N) for no?"<< endl;
				cin >> answer;
				if (answer=="y" || answer=="Y") {
					ptr->next=busLineHead;
					busLineHead=ptr;
					printBusLines(busLineHead);
				}
			}
			else {
				cout << "You are not allowed to add an empty bus line";
			}
		}
	}
}

void addBusStop(busLine* &busLineHead) { //referans parametresi gerekli  (degil galiba)

	string busline, newStop, afterWhat;
	busStop* ptr=new busStop;
	busLine* WhereIsIt=NULL;
	busStop* afterWhereStop=NULL;
	busStop* whereNewStop=NULL;

	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)";
	cin >> busline;

	if (busline!="0") {
		if (!(ifInLine(busline, busLineHead, WhereIsIt))) { 
			cout << "Bus line cannot be found. Going back to previous menu." <<endl;
		}
		else { //if in line 
			cout <<"The bus line information is shown below" <<endl;
			cout << busline << ": " << WhereIsIt->busStops->busStopName;
			busStop* head=WhereIsIt->busStops;
			while(head->right!=NULL) {
				cout << "<->" << head->right->busStopName;
				head=head->right;
			}
			cout <<endl;
			cout <<"Enter the name of the new bus stop: ";
			cin >> newStop;

			if (ifInStop(newStop, WhereIsIt->busStops, whereNewStop)) {  
				cout << "Bus stop already exists. Going back to previous menu." <<endl;
			}
			else {
				cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop): ";
				cin >> afterWhat;
				
				if (afterWhat!="0") {
					bool ifinstop=ifInStop(afterWhat, WhereIsIt->busStops, afterWhereStop);
					while (!(ifinstop)) {
						cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)"; //0 for main menu
						cin >> afterWhat;
					}
					ptr->busStopName=newStop;
					ptr->right=afterWhereStop->right;
					afterWhereStop->right->left=ptr;
					afterWhereStop->right=ptr;
					ptr->left=afterWhereStop;
				}
				else {
					ptr->busStopName=newStop; 
					ptr->right=WhereIsIt->busStops;
					WhereIsIt->busStops->left=ptr;
					WhereIsIt->busStops=ptr; 
				}
				printBusLines(busLineHead);
			}		
		}
	}
}

void deleteBusLine(busLine* &busLineHead) {
	string busline;
	busLine* whereIs=NULL;
	busLine*head=busLineHead;
	busLine*beforeWhereIs=NULL;

	cout << "Enter the name of the bus line to delete: ";
	cin >> busline;

	if(!(ifInLine(busline, busLineHead, whereIs))) {
		cout <<"Bus line cannot be found. Going back to the previous (main) menu."<<endl;
	}
	else { //in line
		if (busLineHead->busLineName!=busline) { //if not at the top
			while(head->next!=whereIs) {
				head=head->next;
			}
			beforeWhereIs=head;
			beforeWhereIs->next=whereIs->next;

			delete whereIs;
		}
		else {
			busLineHead=busLineHead->next;
			delete whereIs;
		}
		printBusLines(busLineHead);
	}
}

void deleteBusStop(busLine* &busLineHead) {
	string busline, bustop;
	busLine* whereIs=NULL;
	busStop* find=NULL;

	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)";
	cin >> busline;
	if (busline!="0") {
		if(ifInLine(busline, busLineHead, whereIs)) {
			cout << "The bus line information is shown below" <<endl;
			cout << whereIs->busLineName << ": " << whereIs->busStops->busStopName;
			busStop* head=whereIs->busStops;			
			while(head->right!=NULL) {
				cout <<"<->" << head->right->busStopName;
				head=head->right;
			}
			cout <<endl;
			cout << "Enter the name of the bus stop to delete (0 for main menu)";
			cin >> bustop;

			if (bustop!="0") {
				while (ifInStop(bustop, whereIs->busStops, find)==false && bustop!="0") { // the one which will be deleted is not there
					cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)"; 
					cin >> bustop;
				}
				if (bustop!="0") {
					//the one which will be deleted is there
					if (find->right!=NULL && find->left!=NULL) {
						find->left->right=find->right;
						find->right->left=find->left;
						delete find;
					}
					if (find->right==NULL) { //at last
						find->left->right=NULL;
						delete find;
					}
					if (find->left==NULL) { //at top
						find->right->left=NULL;
						whereIs->busStops=find->right;
						delete find;
					}
					printBusLines(busLineHead);
				}
			}
		}
		else {
			cout << "Bus line cannot be found. Going back to previous (main) menu." <<endl;
		}
	}
}

void pathfinder(busLine* busLineHead) {
	string StopNow, DestStop;
	vector <busLine*> StopNowLines;
	busLine* WhichLine=NULL;

	cout << "Where are you now?";
	cin >> StopNow;
	cout<< "Where do you want to go?";
	cin >> DestStop;

	busLine* headL=busLineHead;
	
	busStop* headS=headL->busStops;
	if (headS->busStopName==StopNow) { //first line & first stop
		WhichLine=headL;
		StopNowLines.push_back(WhichLine);
	}
	while (headS->right!=NULL) {   //first line & other stops
		if (headS->right->busStopName==StopNow) {
			WhichLine=headL;
			StopNowLines.push_back(WhichLine);
		}
		headS=headS->right;
	}
	while (headL->next!=NULL) {  //other lines
		headS=headL->next->busStops;
		if (headS->busStopName==StopNow) { //other lines & first stops
			WhichLine=headL->next;
			StopNowLines.push_back(WhichLine);
		}
		while (headS->right!=NULL) { //other lines & other stops
			if (headS->right->busStopName==StopNow) {
				WhichLine=headL->next;
				StopNowLines.push_back(WhichLine);
			}
			headS=headS->right;
		}
		headL=headL->next;
	}
	busStop*find=NULL;
	bool ifNoWay=true;

	cout << "You can go there by: " <<endl;
	for (int i=0; i<StopNowLines.size(); i++) {
		//cout << StopNowLines[i]->busLineName << " ";
		if (ifInStop(DestStop, StopNowLines[i]->busStops, find)) { //find is the adress of destination bus stop
			ifNoWay=false;
			cout << StopNowLines[i]->busLineName <<" ";
			busStop* head=StopNowLines[i]->busStops;
			if (head->busStopName==StopNow || head->busStopName==DestStop) {
					
				if (head->busStopName==StopNow) { 
					cout << head->busStopName << "->";
					while (head->right->busStopName!=DestStop) {
						cout << head->right->busStopName << "->";
						head=head->right;
					}
					cout << head->right->busStopName << endl;
				}
				else if (head->busStopName==DestStop) { 
					while (head->right->busStopName!=StopNow) {
						head=head->right;
					}
					cout << head->right->busStopName << "->" << head->busStopName << "->";
					while(head->left->busStopName!=DestStop) {
						cout << head->left->busStopName << "->";
						head=head->left;
					}
					cout << head->left->busStopName <<endl;
				}
			}
			else {
				while (head->right->busStopName!=StopNow && head->right->busStopName!=DestStop) {
					head=head->right;
				}
				if (head->right->busStopName==StopNow) {
					while (head->right->busStopName!=DestStop) {
						cout << head->right->busStopName << "->";
						head=head->right;
					}
					cout << head->right->busStopName << endl;
				}
				else if (head->right->busStopName==DestStop) {
					while (head->right->busStopName!=StopNow) {
						head=head->right;
					}
					cout << head->right->busStopName << "->" << head->busStopName;
					if (head->busStopName!=DestStop) {
						while(head->left->busStopName!=DestStop) {
							cout << head->left->busStopName << "->";
							head=head->left;
						}
						cout << head->left <<endl;
					}
				}
			}
		}
	}
	if (ifNoWay==true) {
		cout << "Sorry no path from "<< StopNow << " to "<< DestStop <<" could be found.";
	}
}


bool consistencyCheck() {
	busLine* currBL = heaD; //a global variable
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
				if(rightBS && rightBS->left != currBS) {
					cout << "Inconsistency for " << currBL->busLineName
					<< " " << currBS->busStopName << endl;
					return false;
				}
				currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

void processMainMenu(busLine* busLineHead, busLine*headLine) {
	char input;
	do
	{
		if(!consistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
			case '0':
				cout << "Thanks for using our program" << endl;
				return;
			case '1':
				printBusLines(busLineHead);
				break;
			case '2':
				addBusLine(headLine, busLineHead);
				break;
			case '3':
				addBusStop(busLineHead);
				break;
			case '4':
				deleteBusLine(busLineHead);
				break;
			case '5':
				deleteBusStop(busLineHead);
				break;
			case '6':
				pathfinder(busLineHead);
				break;
			default:
				cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}

int main() {

	string txtFile, line, busName, Stops;
	ifstream file;

	static busLine* busLineHead = new busLine; //busLineHead will stay the same
	static busLine* headLine=busLineHead;//head will be updated
	headLine->next=NULL;
	
	cout << "Enter filename for reservation database: ";
	cin >> txtFile;
	file.open(txtFile.c_str());
	bool ifFirstLine= true;

	while (getline(file, line)) {
		istringstream eachLine(line);
		eachLine >> busName;
		busName.pop_back();
		busStop* headStop;
		
		if (ifFirstLine) { 
			headLine->busLineName=busName;
			headLine->busStops=new busStop;
			headStop=headLine->busStops;
			ifFirstLine=false;
		}
		else {
			busLine* ptrLine=new busLine;
			ptrLine->next=NULL; 
			ptrLine->busLineName=busName; 
			ptrLine->busStops= new busStop;
			headStop=ptrLine->busStops; //önemli --will be updated
			headLine->next=ptrLine;
			headLine=headLine->next;
		}
		headStop->left=NULL;
		headStop->right=NULL;
		eachLine >> headStop->busStopName;

		while (eachLine >> Stops) {
			busStop* ptr= new busStop;
			ptr->right=NULL; 
			ptr->left=NULL;

			ptr->busStopName=Stops;
			ptr->right=headStop->right; //no need for this actually
			headStop->right=ptr;
			ptr->left=headStop;

			headStop=headStop->right;
		}
	}
	processMainMenu(busLineHead, headLine);
	delete busLineHead;
	return 0;
}