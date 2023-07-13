#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

void AddIdToSorted(vector <int>& myvec) { //to add one Id to a sorted list
	int indexOfCid=myvec.size()-1;
	for (int i=myvec.size()-2; i >=0; i--) { //i starts with the location one before the last element and goes to the first element
		if (myvec[indexOfCid] < myvec[i]) {
			int temp =myvec[i];
			myvec[i]=myvec[indexOfCid];
			myvec[indexOfCid]=temp;
			indexOfCid=i;
		}
	}
}

string soonerOrder(string x, string y) {  //to say which one is sooner on the alphebetical order

	int len1=x.length();
	int len2=y.length();
	
	if (len2 > len1) {
		string temp=y;
		y=x;
		x=temp;
	}

	int i=0;
	while (i< y.length()) {

		if (x[i]>y[i]) {
			return y;
		}
		if (x[i]<y[i]) {
			return x;
		}
		i++;
	}
	return "0";
}

struct courseNode
{
 string courseCode, courseName;
 vector<int> studentsAttendingIDs;
 courseNode * next;
};

courseNode * Deletion(courseNode * &LinkedList, string Ccode, string Cname, int Cid ) { // for option 2

	courseNode *ptr=LinkedList;

	if (ptr->courseCode==Ccode) {
		for (int i=0; i < ptr->studentsAttendingIDs.size(); i++) {
			if (ptr->studentsAttendingIDs[i]==Cid) {
				int position=i;
				for (int k=position+1; k < ptr->studentsAttendingIDs.size(); k++) { // to keep the vector sorted
					int temp=ptr->studentsAttendingIDs[position];
					ptr->studentsAttendingIDs[position]=ptr->studentsAttendingIDs[k];
					ptr->studentsAttendingIDs[k]=temp;
					position=k;
				}
				ptr->studentsAttendingIDs.pop_back();
				cout << "Student with id " << Cid <<" has dropped " << Ccode << "." << endl;
				return LinkedList;
			}
		}
		cout << "Student with id " << Cid << " is not enrolled to " << Ccode << ", thus he can't drop that course." << endl;
		return LinkedList;
	}
	bool continu=true;
	while (ptr->next!=NULL && continu) {//continu in order to prevent infinite loop
		if (ptr->next->courseCode != Ccode) {
			ptr=ptr->next;
		}
		else {
			continu=false;
		}
	}
	if (ptr->next==NULL) {
		cout << "The " << Ccode << " course is not in the list, thus student with id " << Cid << " can’t be dropped" << endl;
		return LinkedList;
	}
	else if (ptr->next->courseCode == Ccode) {
		for (int i=0; i < ptr->next->studentsAttendingIDs.size(); i++) {
			if (ptr->next->studentsAttendingIDs[i]==Cid) {
				int position=i;
				for (int k=position+1; k < ptr->next->studentsAttendingIDs.size(); k++) { //to keep the vector sorted
					int temp=ptr->next->studentsAttendingIDs[position];
					ptr->next->studentsAttendingIDs[position]=ptr->next->studentsAttendingIDs[k];
					ptr->next->studentsAttendingIDs[k]=temp;
					position=k;
				}
				ptr->next->studentsAttendingIDs.pop_back();
				cout << "Student with id " << Cid <<" has dropped " << Ccode << "." << endl;
				return LinkedList;
			}
		}
		cout << "Student with id " << Cid << " is not enrolled to " << Ccode << ", thus he can't drop that course." << endl;
		return LinkedList;
	}
}

courseNode * ConstituteList(courseNode * LinkedList, string Ccode, string Cname, int Cid , int option) {
	//parameter option points if the function is used to get data from the file or the user. if (1) it gets info from the file there will be no cout statements else 
	// it will inform the user about the changes
	courseNode * temp= new courseNode;
	temp->courseName = Cname;
	temp->next = NULL;

	courseNode * ptr= LinkedList;

	if (ptr==NULL) {  // if the linked list is empty
		temp->courseCode=Ccode;
		temp->studentsAttendingIDs.push_back(Cid);
		return temp; 
	}

	if (soonerOrder(Cname, ptr->courseName)==Cname) { //if added one's course name is sooner in alphebetical order
		temp->next=ptr;
		temp->courseCode=Ccode;
		temp->studentsAttendingIDs.push_back(Cid);
		if (option==2) {
			cout << "Student with id " << Cid <<" is enrolled to " << Ccode <<"." <<endl; 
		}
		return temp;
	}

	if (soonerOrder(Cname, ptr->courseName)=="0") { // if Cname==ptr->courseName
		for (int i=0; i < ptr->studentsAttendingIDs.size(); i++) {
			if (Cid == ptr->studentsAttendingIDs[i]) {
				cout << "Student with id " << Cid << " already is enrolled to  " << ptr->courseCode <<". No action taken." <<endl;
				return LinkedList;
			}
		}
		ptr->studentsAttendingIDs.push_back(Cid);
		AddIdToSorted(ptr->studentsAttendingIDs);
		if (option==2) {
			cout << "Student with id " << Cid <<" is enrolled to " << Ccode <<"." <<endl; 
		}
		return LinkedList;
	}

	while (ptr->next != NULL && soonerOrder(ptr->next->courseName, Cname)==ptr->next->courseName) {  
		ptr=ptr->next;	
	}

	if (ptr->next == NULL) { 
		ptr->next=temp;
		temp->courseCode=Ccode;
		temp->studentsAttendingIDs.push_back(Cid);
		if (option==2) {
			cout << "Student with id " << Cid <<" is enrolled to " << Ccode <<"." <<endl; 
		}
		return LinkedList;
	}

	if (soonerOrder(ptr->next->courseName, Cname)=="0") { //if Cname=ptr->next->courseName

		for (int i=0; i < ptr->next->studentsAttendingIDs.size(); i++) {
			if (ptr->next->studentsAttendingIDs[i]==Cid) {
				cout << "Student with id " << Cid << " already is enrolled to " << Ccode << ". No action taken." << endl;
				return LinkedList;
			}	
		}
		ptr->next->studentsAttendingIDs.push_back(Cid);
		AddIdToSorted(ptr->next->studentsAttendingIDs);
		if (option==2) {
			cout << "Student with id " << Cid <<" is enrolled to " << Ccode <<"." <<endl; 
		}
		return LinkedList;
	}

	if (soonerOrder(ptr->next->courseName, Cname)==Cname) { //ptr->next->courseCode > Ccode
		temp -> next = ptr -> next;
		ptr -> next = temp;
		temp->courseCode=Ccode;
		temp->studentsAttendingIDs.push_back(Cid);
		AddIdToSorted(temp->studentsAttendingIDs);
		if (option==2) {
			cout << "Student with id " << Cid <<" is enrolled to " << Ccode <<"." <<endl; 
		}
		return LinkedList;
	}
}

void DeleteList (courseNode *head) {  //from the slides -> to return the memory to the heap
  courseNode *temp;				
  while (head != NULL) {				
      temp = head->next;			
      delete head;
      head = temp;
  }
}


int main() {

	string txtFile, line, Ccode, Cname, choice;
	ifstream file;
	int Cid;
	courseNode * LinkedListHead = NULL;
	
	cout << "Enter filename for reservation database: ";
	cin >> txtFile;
	file.open(txtFile.c_str());

	while (getline(file, line)) {
		istringstream eachLine(line);
		eachLine >> Ccode >> Cname >> Cid;
		LinkedListHead= ConstituteList(LinkedListHead, Ccode, Cname, Cid, 1);
	}

	courseNode * pointer=LinkedListHead;
	cout << "The linked list is created." <<endl;
	cout << "The initial list is:" <<endl;
	
	while (pointer->next!=NULL) {
		cout << pointer->courseCode << " " << pointer->courseName << ": ";
		for (int i=0; i < pointer->studentsAttendingIDs.size(); i++) {
			cout << pointer->studentsAttendingIDs[i] << " ";
		}
		cout << endl;
		pointer=pointer->next;
	}
	cout << pointer->courseCode << " " << pointer->courseName << ": ";
	for (int i=0; i < pointer->studentsAttendingIDs.size(); i++) {
		cout << pointer->studentsAttendingIDs[i] << " ";
	}
	cout << endl;

	cout << "Please select one of the choices:" << endl;
	cout << "1. Add to List" << endl;
	cout << "2. Drop from List" << endl;
	cout << "3. Display List" << endl;
	cout << "4. Finish Add/Drop and Exit" << endl;
	cin >> choice;

	while (choice != "4") {

		if (choice=="1") {
			
			string each, line;
			int which=1;

			cout << "Give the student ID and the course names and course codes that he/she wants to add: ";

			string CourseCode;
			string CourseName;

			cin.get();  //önemli
			getline(cin, line);

			istringstream s(line);

			while (s >> each) {

				if (isalpha(each[0])) { // the words that starts with letters consist of course codes and names in series
					if (which==1) {
						CourseCode=each;
						which++;
					}
					else if (which==2) {
						CourseName=each;
						which--;
					}
				}

				if (!(isalpha(each[0]))) {
					int intID=atoi(each); 
					LinkedListHead=ConstituteList(LinkedListHead, CourseCode, CourseName, intID, 2);
				}			
			}
			/*
			//to control
			courseNode * pointer=LinkedListHead;
	
			while (pointer->next!=NULL) {
				cout << pointer->courseCode<< endl;
				for (int i=0; i < pointer->studentsAttendingIDs.size(); i++) {
					cout << pointer->studentsAttendingIDs[i] << " ";
				}
				cout << endl;
				pointer=pointer->next;
			}
			cout << pointer->courseCode <<endl;
			for (int i=0; i < pointer->studentsAttendingIDs.size(); i++) {
				cout << pointer->studentsAttendingIDs[i] << " ";
			}
			cout << endl;
			*/
		}
		if (choice=="2") {

			string each, line;
			int which=1;			

			cout << "Give the student ID and the course names and course codes that he/she wants to drop: ";

			string CourseCode;
			string CourseName;
			
			cin.get();
			getline(cin, line);
			istringstream s(line);

			while (s >> each) {

				if (isalpha(each[0])) {
					if (which==1) {
						CourseCode=each;
						which++;
					}
					else if (which==2) {
						CourseName=each;
						which--;
					}
				}

				if (!(isalpha(each[0]))) {
					int intID=atoi(each); 
					LinkedListHead=Deletion(LinkedListHead, CourseCode, CourseName, intID);
				}			
			}
		}
		if (choice=="3") {
			courseNode * pointer=LinkedListHead;
	
			while (pointer->next!=NULL) {
				cout << pointer->courseCode << " " << pointer->courseName << ": ";
				for (int i=0; i < pointer->studentsAttendingIDs.size(); i++) {
					cout << pointer->studentsAttendingIDs[i] << " ";
				}
				cout << endl;
				pointer=pointer->next;
			}
			cout << pointer->courseCode << " " << pointer->courseName << ": ";
			for (int i=0; i < pointer->studentsAttendingIDs.size(); i++) {
				cout << pointer->studentsAttendingIDs[i] << " ";
			}
			cout << endl;
		}
		
		cout << "Please select one of the choices:" << endl;
		cout << "1. Add to List" << endl;
		cout << "2. Drop from List" << endl;
		cout << "3. Display List" << endl;
		cout << "4. Finish Add/Drop and Exit" << endl;
		cin >> choice;

	}
	cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
	cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;

	while (LinkedListHead!=NULL) {
		cout << LinkedListHead->courseCode << " " << LinkedListHead->courseName;
		
		if (LinkedListHead->studentsAttendingIDs.size() >= 3) {
			cout << ": ";
			for (int i=0; i < LinkedListHead->studentsAttendingIDs.size(); i++) {
				cout << LinkedListHead->studentsAttendingIDs[i] << " ";
			}
			cout << endl;
		}
		else {
			cout << " -> This course will be closed." <<endl;
		}
		
		LinkedListHead=LinkedListHead->next;
	}

	 DeleteList (LinkedListHead);

	return 0;
}
