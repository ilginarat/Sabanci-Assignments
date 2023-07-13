#include <iostream>
#include "DynStuQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynStuQueue::DynStuQueue()
{
	front = NULL;
	rear = NULL;   
	#ifdef _DEBUG
		cout << "An empty queue has been created\n";
	#endif
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynStuQueue::enqueue(student num)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(num);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(num);
		rear = rear->next;
	} 
	/*
	#ifdef _DEBUG
		cout << num.name << " enqueued\n";   /////////SORUN NE???????????????///////////
	#endif
	*/
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynStuQueue::dequeue(student &num)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num = front->value;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynStuQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynStuQueue::clear()
{
	student value;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(value); //delete all elements
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif
}