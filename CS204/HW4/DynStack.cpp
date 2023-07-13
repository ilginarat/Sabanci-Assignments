#include <iostream>
#include <string>
#include "DynStack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynStack::DynStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynStack::push(duo str)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value = str;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynStack::pop(duo &str)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		str = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

