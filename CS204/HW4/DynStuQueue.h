#ifndef DYNSTUQUEUE_H
#define DYNSTUQUEUE_H

#include <string>
using namespace std;

struct student {

	string name, request;
	int ID;
};

struct QueueNode
{
	student value;
	QueueNode *next;
	QueueNode(student num, QueueNode *ptr = NULL)
	{
		value = num;
		next = ptr;
	}
};

class DynStuQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	DynStuQueue();
	
	// Member functions.
	void enqueue(student);
	void dequeue(student &);
	bool isEmpty() const;     
	void clear();
};
#endif