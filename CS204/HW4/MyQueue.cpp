#include <iostream>
#include <string>
#include "MyQueue.h"
using namespace std;

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************

MyQueue::MyQueue(int s)
{
	queueArray = new instructor[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
	#ifdef _DEBUG
		cout << "A queue with " << s << " elements created\n";
	#endif
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void MyQueue::enqueue(instructor num)
{
	if (isFull())
    { 
         cout << "The queue is full. " << num.name << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = num;
		// Update item count.
		numItems++;
		#ifdef _DEBUG
			cout << num.name << " enqueued\n";
		#endif
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void MyQueue::dequeue(instructor &num)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		num = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool MyQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool MyQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void MyQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif
}