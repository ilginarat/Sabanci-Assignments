#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MyQueue.h"
#include "DynStuQueue.h"
#include "DynStack.h"

using namespace std;

struct node {

	string aim;
	node* next;
	node* nextFunc;

	node::node() { 
		next=NULL;
		nextFunc=NULL;
	}
};

void addInstructorRequest(MyQueue &InsQueue) {
	string func, insName;
	int id;

	cout << "Add a function instructor wants to use";
	cin>>func;
	instructor i;
	i.request=func;
	cout << "Give the instructor's name";
	cin >>insName;
	i.name=insName;
	cout <<"Give the Id";
	cin>>id;
	i.ID=id;
	InsQueue.enqueue(i);
}

void addStudentRequest(DynStuQueue &StuQueue) {

	string func, stuName;
	int id;

	cout << "Add a function student wants to use";
	cin>>func;
	student s;
	s.request=func;
	cout << "Give the student's name";
	cin >>stuName;
	s.name=stuName;
	cout <<"Give the Id";
	cin>>id;
	s.ID=id;
	StuQueue.enqueue(s);
}

void printStack(DynStack& Stack) {

	DynStack temp;
	duo var, var2;

	cout <<"PRINTING THE STACK TRACE:"<< endl;

	if (Stack.isEmpty()) {
		cout <<"The stack is empty" <<endl;
	}

	while (!(Stack.isEmpty())) {

		Stack.pop(var);
		//cout << var.name << "from" << var.func <<endl;

		temp.push(var);
	}
	while (!(temp.isEmpty())) {

		temp.pop(var2);
		cout << var2.func << ": define " << var2.name <<endl;
		Stack.push(var2);
	}
}

void processARequest(string functionName, node* HEAD, DynStack& Stack) {

	node*h=HEAD;
	string var, type;

	while (h!=NULL) {
		if (h->aim==functionName) {
			break;
		}
		h=h->nextFunc;
	}
	// h is the name of the func
	while (h->next!=NULL)
	{
		istringstream s(h->next->aim);
		s >> type >> var;
		
		if(type =="define")
		{
			duo d;
			d.name=var;
			d.func=functionName;
			Stack.push(d);
		}
		else if (type=="call")
		{
			cout << "calling " << var << " from " << functionName << endl;
			processARequest(var,  HEAD, Stack);
		}	
		else {
			printStack(Stack);
		}
		h=h->next;
	}
	// delete 
	cout << functionName <<" is finished. Clearing the stack from it's data... " <<endl;

 	duo p;
	Stack.pop(p);
	Stack.push(p);

	while (!(Stack.isEmpty()) && p.func==functionName) {
		Stack.pop(p);
		if (!(Stack.isEmpty())) {
			Stack.pop(p);
			Stack.push(p);
		}
	}

	system("pause");
}

void processARequest(MyQueue &InsQueue, DynStuQueue &StuQueue, node* HEAD, DynStack& Stack)
{
	instructor i;
	student s;

	if (!InsQueue.isEmpty()) {
		InsQueue.dequeue(i);
		cout << "Processing instructors queue" <<endl;
		cout << "Processing Prof. " << i.name << "s reguest (with ID "<< i.ID << " ) of service (" << i.request << ")" <<endl;

		processARequest(i.request, HEAD, Stack);
		cout << "The stack is empty" <<endl;
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!StuQueue.isEmpty()) {
	 
		StuQueue.dequeue(s);
		cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		cout << "Processing " << s.name << "s reguest (with ID "<< s.ID << " ) of service (" << s.request << ")" <<endl;

		processARequest(s.request, HEAD, Stack);
		cout << "The stack is empty" <<endl;
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else
	{
		cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
	}
}

int main (){

	string key, filename, line, firstFuncName, filename2, line2;
	ifstream myFile, myFile2;
	MyQueue InsQueue(5); // static queue for instructors--------5 sallamasyon
	DynStuQueue StuQueue; //Dynamic queue for students
	DynStack Stack;
	//here

	node* HEAD= new node; //for all the nodes  ---dont forget
	node* headfunc=HEAD;
	cout <<"If you want to open a servise (function) defining a file," << endl <<" then press (y or Y) for yes, otherwise press any single key: ";
	cin>>key;
	
	if (key=="y" || key=="Y") {   //for the first function
		cout << "Enter the input file name: ";
		cin>>filename;
		myFile.open(filename.c_str());

		getline(myFile, firstFuncName);
		firstFuncName.pop_back();
		HEAD->aim=firstFuncName;
		node* head=headfunc;

		while (getline(myFile, line)) { 
			node*newNode=new node;
			head->next=newNode;
			line.pop_back();
			newNode->aim=line;  
			head=head->next;
		}
		cout <<"Do you want to open another service defining file?" << endl <<"Press (y or Y) for yes, otherwise press any single key: ";
		cin >>key;
	}	

	while (key=="y" || key=="Y") { //for each funct (except the first)
		
		cout <<"enter the name of the file ";
		cin>>filename2;
		myFile2.open(filename2.c_str());
		
		getline(myFile2, line2);  
		node*newFuncNode=new node;
		headfunc->nextFunc=newFuncNode;
		line2.pop_back();
		newFuncNode->aim=line2;
		headfunc=headfunc->nextFunc;
		
		node* head=headfunc;
		while (getline(myFile2, line2)) { //for each line

			node*newNode=new node;
			head->next=newNode;
			line2.pop_back();
			newNode->aim=line2;
			head=head->next;
		}
		myFile2.close(); //impotrant
		cout <<"Do you want to open another service defining file?" << endl <<"Press (y or Y) for yes, otherwise press any single key: ";
		cin >>key;
	}
	//until here

	while (true){
		cout << endl;
		cout<<"**********************************************************************"<<endl
		<<"**************** 0 - EXIT PROGRAM *************"<<endl
		<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
		<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
		<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
		<<"**********************************************************************"<<endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin>>option;
		switch (option)
		{
			case 0:
				cout<<"PROGRAM EXITING ... "<<endl;
				system("pause");
				exit(0);
			case 1:
				addInstructorRequest(InsQueue);
				break;
			case 2:
				addStudentRequest(StuQueue);
				break;
			case 3:
				processARequest(InsQueue, StuQueue, HEAD, Stack);
				break;
			default:
				cout<<"INVALID OPTION!!! Try again"<<endl;
		}//switch
	}//while (true)

	return 0;
}