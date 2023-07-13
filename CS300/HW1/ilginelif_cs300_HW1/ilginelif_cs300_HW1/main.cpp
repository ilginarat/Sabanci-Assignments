//  Created by Ilgın Arat on 22.03.2022.

#include <string>
#include <vector>
#include "tStack.h"
#include "randgen.h"
#include "strutils.h"
#include <fstream>
#include <iostream>
#include "tStack.cpp"
using namespace std;

struct cell {
    int   x;
    int   y;
    int   up=1;   // will be equal to 1 if there is a wall, else 0
    int   down=1;
    int   right=1;
    int   left=1;
    bool visited;
    
    cell(int xx = 0, int yy = 0,bool v = false):x(xx),y(yy),visited(v) {};
    
    bool operator == (const cell & a) {
        if (x==a.x && y==a.y) {
            return true;
        }
        else {
            return false;
        }
    }
};

bool ifPossible (cell myCell) { //oraya gidebilir miyim
    
    if (myCell.visited==true || myCell==cell(-1,-1)) {
        return false;
    }
    return true;
}

cell &findCell (int x, int y, vector <cell>& myVec, cell &null) { //return by reference?
    
    for (int i =0; i<myVec.size(); i++) {
        if (myVec[i].x==x && myVec[i].y==y) {
            return myVec[i]; //bu kendisini return ediyor değil mi?
        }
    }
    return null; //NULL
}

bool thereIsWay (int rows, int cols, Stack<cell>& myStack, vector <cell> myVec) { //to generate the maze
    
    cell useAsNull= cell(-1, -1);
    const ListNode<cell>* current=myStack.top();
    int x=current->value.x;
    int y=current->value.y;
    
    if (ifPossible (findCell (x+1, y, myVec, useAsNull)) || ifPossible (findCell (x-1, y, myVec, useAsNull)) || ifPossible (findCell (x, y-1, myVec, useAsNull)) || ifPossible (findCell (x, y+1, myVec, useAsNull))) {
        return true;
    }
    else {
        return false;
    }
}

bool allVisited (vector <cell> &myVec) {
    
    for (int i =0; i<myVec.size(); i++) {
            if (myVec[i].visited==false) { //check if all visited if there is one no
                return false;
            }
    }
    return true;
}

bool findWay (cell currentCell, vector <cell> &myVec) {  //to find a path
    
    cell useAsNull=cell(-1, -1);
    
    if (currentCell.right==0 && findCell(currentCell.x+1, currentCell.y, myVec, useAsNull).visited==false ) {
        return true;
    }
    else if (currentCell.left==0 && findCell(currentCell.x-1, currentCell.y, myVec, useAsNull).visited==false ) {
        return true;
    }
    else if (currentCell.up==0 && findCell(currentCell.x, currentCell.y+1, myVec, useAsNull).visited==false ) {
        return true;
    }
    else if (currentCell.down==0 && findCell(currentCell.x, currentCell.y-1, myVec, useAsNull).visited==false ) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    vector <cell> myVec;
    int num, rows, cols;
    cell useAsNull= cell(-1,-1);
    ofstream maze_out, path_out;
    
    string filename="maze_1.txt";
    maze_out.open(filename.c_str());
    
    cout << "Enter the number of mazes: ";
    cin >> num;
    
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> rows >>cols;
    
    maze_out << cols << " " << rows <<endl;
    
    cout << "All mazes are generated." <<endl;
    
    //creating the cells
    for (int i =0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            cell myCell(j,i);
            myVec.push_back(myCell);
        }
    }
    int NumOfMazes=0;
    while(NumOfMazes!=num) {
    
        Stack<cell> myStack;
        findCell(0,0,myVec, useAsNull).visited=true;
        cell firstCell=findCell(0,0,myVec, useAsNull);
        myStack.push(firstCell);
        
        RandGen randGen;
        int whatToDo;
        int x, y;
        while (!(allVisited(myVec))) { //hepsi visited olmadığı sürece
            
            if (thereIsWay(rows,cols, myStack, myVec)) {
                
                x=myStack.top()->value.x;
                y=myStack.top()->value.y;
                
                whatToDo=randGen.RandInt(0, 3); //0:right, 1:left, 2:up, 3:down

                if (whatToDo==0) {
                    x++;
                }
                else if (whatToDo==1) {
                    x--;
                }
                else if (whatToDo==2) {
                    y++;
                }
                else if (whatToDo==3) {
                    y--;
                }
                            //öyle bir cell yoksa                  cell zaten visited ise
                while (findCell(x, y, myVec, useAsNull)==cell(-1,-1) || ifPossible(findCell(x, y, myVec, useAsNull))==false ) {
                    
                    x=myStack.top()->value.x;
                    y=myStack.top()->value.y;
                    
                    whatToDo=randGen.RandInt(0, 3);
                    
                    if (whatToDo==0) {
                        x++;
                    }
                    else if (whatToDo==1) {
                        x--;
                    }
                    else if (whatToDo==2) {
                        y++;
                    }
                    else if (whatToDo==3) {
                        y--;
                    }
                }
                cell currentTop;
                int ctX, ctY;
                findCell(x, y, myVec, useAsNull).visited=true; // the next cell becomes true
                
                if (whatToDo==0) {
                    findCell(x, y, myVec, useAsNull).left=0; //next cell's left is broken
                    currentTop=myStack.topAndPop();
                    ctX=currentTop.x;
                    ctY=currentTop.y;
                    findCell(ctX, ctY, myVec, useAsNull).right=0;
                    myStack.push(findCell(ctX, ctY, myVec, useAsNull));
                }
                else if (whatToDo==1) {
                    findCell(x, y, myVec, useAsNull).right=0;
                    currentTop=myStack.topAndPop();
                    ctX=currentTop.x;
                    ctY=currentTop.y;
                    findCell(ctX, ctY, myVec, useAsNull).left=0;
                    myStack.push(findCell(ctX, ctY, myVec, useAsNull));
                }
                else if (whatToDo==2) {
                    findCell(x, y, myVec, useAsNull).down=0;
                    currentTop=myStack.topAndPop();
                    ctX=currentTop.x;
                    ctY=currentTop.y;
                    findCell(ctX, ctY, myVec, useAsNull).up=0;
                    myStack.push(findCell(ctX, ctY, myVec, useAsNull));
                }
                else if (whatToDo==3) {
                    findCell(x, y, myVec, useAsNull).up=0;
                    currentTop=myStack.topAndPop();
                    ctX=currentTop.x;
                    ctY=currentTop.y;
                    findCell(ctX, ctY, myVec, useAsNull).down=0;
                    myStack.push(findCell(ctX, ctY, myVec, useAsNull));
                }
                
                myStack.push(findCell(x, y, myVec, useAsNull)); //push next cell
            }
            
            else { //if there is no way
                
                while (!(thereIsWay(rows, cols, myStack, myVec))) {
                    myStack.pop();
                    //cout << "popladım"<<endl;
                }
            }
        }
        NumOfMazes++;
    }
    
    
    for (int k=0; k<myVec.size(); k++) {
        maze_out << "x=" << myVec[k].x << " y=" << myVec[k].y << " l=" << myVec[k].left << " r=" << myVec[k].right << " u=" << myVec[k].up << " d=" << myVec[k].down <<endl;
    }
    maze_out.close();
    //pathFinder part
    //hangi maze'i kullanacağını seç
    
    Stack<cell> findStack;
    int sX, sY, fX, fY;
    
    cout << "Enter the start: ";
    cin >> sX >> sY;
    
    cout << "Enter the finishing coordinates: ";
    cin >> fX >> fY;
    
    string filename2= "maze_1_path_" + itoa(sX) + "_" + itoa(sY) + "_" + itoa(fX) + "_" + itoa(fY) + ".txt";
    path_out.open(filename2.c_str());
    
    //make all the cells not visited
    for (int i =0; i<myVec.size(); i++) {
        myVec[i].visited=false;
    }
//   start cell
    findCell(sX, sY, myVec, useAsNull).visited=true;
    findStack.push(findCell(sX, sY, myVec, useAsNull));
    
    cell currentCell=findStack.top()->value; //shallow copy
    cell newCell;
    
    while (currentCell.x!=findCell(fX, fY, myVec, useAsNull).x || currentCell.y!=findCell(fX, fY, myVec, useAsNull).y) { //finish e ulaşamadığın sürece
        
        if (findWay (currentCell, myVec)) { //if there is a way to go
            
            RandGen randGen2;
            int whatToDo2;
            whatToDo2=randGen2.RandInt(0, 3);
            
            int newX, newY;
            
            bool goOn=true;
            while (goOn) {
                if (whatToDo2==0) {
                    if (currentCell.right==0 && findCell(currentCell.x+1, currentCell.y, myVec, useAsNull).visited==false) {
                        newX=currentCell.x+1;
                        newY=currentCell.y;
                        goOn=false;
                    }
                }
                else if (whatToDo2==1) {
                    if (currentCell.left==0 && findCell(currentCell.x-1, currentCell.y, myVec, useAsNull).visited==false) {
                        newX=currentCell.x-1;
                        newY=currentCell.y;
                        goOn=false;
                    }
                }
                else if (whatToDo2==2) {
                    if (currentCell.up==0 && findCell(currentCell.x, currentCell.y+1, myVec, useAsNull).visited==false) {
                        newX=currentCell.x;
                        newY=currentCell.y+1;
                        goOn=false;
                    }
                }
                else if (whatToDo2==3) {
                    if (currentCell.down==0 && findCell(currentCell.x, currentCell.y-1, myVec, useAsNull).visited==false) {
                        newX=currentCell.x;
                        newY=currentCell.y-1;
                        goOn=false;
                    }
                }
                whatToDo2=randGen2.RandInt(0, 3);
            }
            findCell(newX, newY, myVec, useAsNull).visited=true;
            findStack.push(findCell(newX, newY, myVec, useAsNull));
            currentCell=findStack.top()->value; //bu gerekli dimi?
        }
        else {
            findStack.pop( );
            currentCell=findStack.top()->value;
            //cout << "popladım"<<endl;
        }
    }
    //path_out a yazalım
    
    Stack<cell> writingStack;
    while (findStack.isEmpty()!=true) {
        writingStack.push(findStack.topAndPop());
    }
    
    while (writingStack.isEmpty()!=true) {
        cell byeCell= writingStack.topAndPop();
        path_out << byeCell.x << " " << byeCell.y <<endl;
    }
    
    path_out.close();
    
    return 0;
}
