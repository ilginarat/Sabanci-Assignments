#include <string>
using namespace std;

struct instructor {

	string name, request;
	int ID;
};

class MyQueue
{
private:
	instructor *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	MyQueue(int);  //constructor, parameter is capacity
  	void enqueue(instructor); 
  	void dequeue(instructor &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
