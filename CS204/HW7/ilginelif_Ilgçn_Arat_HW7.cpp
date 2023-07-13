/**Artrim Kjamilji, 20.12.2021**/

/*include all the necessary files, libraries, etc. here, if any*/

#include "strutils.h"
#include <string>  //bu gereksiz olmalýydý??

#include "Shape.h"
#include "TwoDShape.h"
#include "ThreeDShape.h"
#include "rectangle.h"
#include "Box.h"

using namespace std;

/*char getchar() {
	char a;
	cin>>a;
	return a;
}*/

Shape* getShape() { //it needs to be a pointer
	int opt;
	float w, l, h;
	string n;
	Shape* ptr;

	cout << "choose an option <1 or 2>: " << endl << "1. Rectangle" <<endl << "2. Box" <<endl;
	cin>> opt;
	while (opt!=1 && opt!=2) {
		cout << "UNAVAILABLE OPTION CHOSEN. Try again."<<endl<<endl;
		cout << "choose an option <1 or 2>: " << endl << "1. Rectangle" <<endl << "2. Box" <<endl;
		cin>> opt;
	}
	if (opt==1) {
		cout << "You chose rectangle. Give it's width, lenght and name: " << endl;
		cin >> w >> l >>n;
		ptr = new rectangle( n, w, l);
	}
	else if (opt==2) {
		cout << "You chose box. Give it's width, lenght, height and name: " << endl;
		cin >> w >> l >> h >> n;
		ptr= new Box( n, w, l, h);
	}
	else {   //no need
		ptr=NULL;
	}
	return ptr;
}

int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	Shape *shape_1, *shape_2; 
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}
