#include <string>
using namespace std;

struct duo {

	string name;
	string func;
};

struct StackNode
{
	duo value;
	StackNode *next;
};

class DynStack
{
private:

public:
	StackNode *top;
	DynStack(void);
	void push(duo);
	void pop(duo &);
	bool isEmpty(void);
};
