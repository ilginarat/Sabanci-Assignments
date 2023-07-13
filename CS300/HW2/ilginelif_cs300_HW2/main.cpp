//  Created by Ilgın Arat on 8.04.2022.

#include "BST.h"
#include "BST.cpp"
#include "AVL.h"
#include "AVL.cpp"  //I wrote the remove function of AVL but it does not work well so I commented them out in the main.
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct content {
    string title;
    string info;
    bool ifsection;
    string section="";
    
    bool operator < (content & x) {
        if (title < x.title ) {   //alphebetical order
            return true;
        }
        else {
            return false;
        }
    }
    
    bool operator > (content & x) {
        if (title > x.title) {
            return true;
        }
        else {
            return false;
        }
    }
    
    bool operator != (content & x) {
        
        if (title==x.title) {
            return false;
        }
        else return true;
    }
    
    bool operator == (content & x) {
        
        if (title==x.title) {
            return true;
        }
        else return false;
    }
};

void travelAndChange(BinaryNode<content> *root, bool toWhat, bool itsSection) { //to print sections & to make all nodes true
    
    if (root->element.ifsection==itsSection) {
        root->ifSuitable=toWhat;
    }
    if (root->left!=NULL) {
        travelAndChange(root->left, toWhat, itsSection);
    }
    if (root->right!=NULL) {
        travelAndChange(root->right, toWhat, itsSection);
    }
}

void travelAndChangeAVL(AvlNode<content> *root, bool toWhat, bool itsSection) { //to print sections & to make all nodes true
    
    if (root->element.ifsection==itsSection) {
        root->ifSuitable=toWhat;
    }
    if (root->left!=NULL) {
        travelAndChangeAVL(root->left, toWhat, itsSection);
    }
    if (root->right!=NULL) {
        travelAndChangeAVL(root->right, toWhat, itsSection);
    }
}

void travelAndRemove(BinaryNode<content> *root, BinarySearchTree<content> & myTree) { //bunu template yapabilir miyim mesela???------********-------*****
    
    if (root->ifSuitable==true) {
        myTree.remove( root->element );
    }
    if (root->left!=NULL) {
        travelAndRemove(root->left, myTree);
    }
    if (root->right!=NULL) {
        travelAndRemove(root->right, myTree);
    }
}

void travelAndRemoveAVL(AvlNode<content> *root, AvlTree<content> & myTree) {
    
    if (root->ifSuitable==true) {
        myTree.remove( root->element );
    }
    if (root->left!=NULL) {
        travelAndRemoveAVL(root->left, myTree);
    }
    if (root->right!=NULL) {
        travelAndRemoveAVL(root->right, myTree);
    }
}

void itemPrinter(BinaryNode<content> *root, string itsSection) { //to adjust ifSuitable
    
    if (root->element.section!=itsSection) {
        root->ifSuitable=false;
    }
    if (root->left!=NULL) {
        itemPrinter(root->left, itsSection);
    }
    if (root->right!=NULL) {
        itemPrinter(root->right, itsSection);
    }
}

void itemPrinterAVL(AvlNode<content> *root, string itsSection) { //to adjust ifSuitable
    
    if (root->element.section!=itsSection) {
        root->ifSuitable=false;
    }
    if (root->left!=NULL) {
        itemPrinterAVL(root->left, itsSection);
    }
    if (root->right!=NULL) {
        itemPrinterAVL(root->right, itsSection);
    }
}

void sectionPrinter(BinaryNode<content> *root, string itsSection) { //to adjust ifSuitable
    
    if (root->element.title==itsSection) {
        root->ifSuitable=true;
    }
    if (root->left!=NULL) {
        itemPrinter(root->left, itsSection);
    }
    if (root->right!=NULL) {
        itemPrinter(root->right, itsSection);
    }
}

void ifSection(string line, BinarySearchTree<content> & myTree, string &mySection) {
    content x;
    x.title=line;
    x.ifsection=true;
    myTree.insert(x);
    
    mySection=line;
}

void ifSectionAVL(string line, AvlTree<content> & myTree, string &mySection) {
    content x;
    x.title=line;
    x.ifsection=true;
    myTree.insert(x);
    
    mySection=line;
}

void ifItem(string line, BinarySearchTree<content> & myTree, string mySection) {
    content x;
    line=line.replace(0,1,"");
    int index=line.find("-");
    x.title=line.substr(0, index);
    int len=line.length();
    x.info=line.substr(index+1,len-index-1);
    
    x.ifsection=false;
    x.section=mySection;
    
    myTree.insert(x);
}

void ifItemAVL(string line, AvlTree<content> & myTree, string mySection) {
    content x;
    line=line.replace(0,1,"");
    int index=line.find("-");
    x.title=line.substr(0, index);
    int len=line.length();
    x.info=line.substr(index+1,len-index-1);
    
    x.ifsection=false;
    x.section=mySection;
    
    myTree.insert(x);
}

void printSection( BinaryNode<content> *root )
{
      if ( root != NULL )
      {
          printSection ( root->left );
            if (root->ifSuitable== true) {
              cout << root->element.title << endl;
            }
          printSection( root->right );
      }
}

void printSectionAVL( AvlNode<content> *root )
{
      if ( root != NULL )
      {
          printSectionAVL ( root->left );
            if (root->ifSuitable== true) {
              cout << root->element.title << endl;
            }
          printSectionAVL( root->right );
      }
}

void printItem( BinaryNode<content> *root )
{
      if ( root != NULL )
      {
          printItem ( root->left ); 
            if (root->ifSuitable== true) {
              cout << root->element.title << endl;
            }
          printItem( root->right );
      }
}

void printItemAVL( AvlNode<content> *root )
{
      if ( root != NULL )
      {
          printItemAVL ( root->left );
            if (root->ifSuitable== true) {
              cout << root->element.title << endl;
            }
          printItemAVL( root->right );
      }
}

int main() {
    
    content a;
    a.title="";
    a.info="";
    const content ITEM_NOT_FOUND = a;
    BinarySearchTree<content> myTree(a);
    AvlTree <content> myAVLTree(a);
    
    string filename="data.txt", line;
    ifstream myFile;
    myFile.open(filename.c_str());
    
    if (myFile.fail()) {
        cout << "failed";
    }
    cout << "Welcome to the Notebook!" <<endl;
    string mySection, Section;
    
    auto start=chrono::high_resolution_clock::now();
    while (getline(myFile, line)) {
        
        if (line[0]=='-') {
            ifItem(line, myTree, mySection); //for BST
        }
        else {
            ifSection(line, myTree, mySection); //for BST
        }
    }
    auto end=chrono::high_resolution_clock::now();
    long long timer = (end-start).count();
    cout << "BST Notebook has been inserted." <<endl;
    cout << "[BST] Elapsed time: " << timer << "microseconds" << std::endl;


    myFile.clear();
    myFile.seekg(0);
    
    auto start2=chrono::high_resolution_clock::now();
    while (getline(myFile, line)) {
        
        if (line[0]=='-') {
            ifItemAVL(line, myAVLTree, mySection); // for AVL
        }
        else {
            ifSectionAVL(line, myAVLTree, mySection); //for AVL
        }
    }
    auto end2=chrono::high_resolution_clock::now();
    long long timer2 = (end2-start2).count();
    cout << "AVL Notebook has been inserted." <<endl;
    cout << "[AVL] Elapsed time: " << timer2 << "microseconds" << std::endl;
    
    
    int choice, choice2;
    cout << "MENU" << endl << "Please enter an input between [1 - 6]:" << endl << "1- Display the sections [AVL]" << endl << "2- Display the sections [BST]" << endl << "3- Select a section" << endl << "4- Add new section" << endl << "5- Delete a section" << endl << "6- Exit" << endl << "Input: ";
    cin >> choice;
    
    while (choice !=6) {
        
        if (choice ==1 ) { //Display the sections (AVL)
            
            travelAndChangeAVL(myAVLTree.root, false, false);
            printSectionAVL(myAVLTree.root);
            travelAndChangeAVL(myAVLTree.root, true, false);
        }
        
        if (choice ==2 ) { //Display the sections (BST)
            
            //itemlerin hepsini ifSuitable=false yap
            travelAndChange(myTree.root, false, false);
            printSection(myTree.root);
            travelAndChange(myTree.root, true, false);
        }
                
        if (choice ==3 ) { //Select a section
            
            cout << "Enter the title of the section: ";
            cin >> Section;
            cout << "Selected section -> " << Section <<endl;
            cout << "Please enter an input between [1 - 7]: " << endl << "1- Display the items [AVL]" << endl << "2- Display the items [BST]" << endl << "3- Display the information of a item" << endl <<" 4- Add new item" << endl << "5- Update the information of a item" << endl << "6- Delete an item" << endl << "7- Return to main menu" <<endl << "Input: ";
            cin >> choice2;
            
            if (choice2 == 1) { // Display the items (AVL)
                itemPrinterAVL(myAVLTree.root, Section);
                printItemAVL(myAVLTree.root);
                travelAndChangeAVL(myAVLTree.root, true, true);
                travelAndChangeAVL(myAVLTree.root, true, false);
            }
            if (choice2 == 2) { // Display the items (BST)
                itemPrinter(myTree.root, Section);
                printItem(myTree.root);
                travelAndChange(myTree.root, true, true);
                travelAndChange(myTree.root, true, false);
            }
            if (choice2 == 3) {  //Display the info of an item
                string nameItem;
                cout << "Enter the title of the item: ";
                cin >> nameItem;
                content m, searched;
                m.section=Section;
                m.title=nameItem;
                m.ifsection=false;
                
                if (myTree.find(m)!=a) {
                
                    auto start=chrono::high_resolution_clock::now();
                    searched=myTree.find(m);  //for BST
                    auto end=chrono::high_resolution_clock::now();
                    long long timer = (end-start).count();
                    cout << "[BST] Elapsed time of: " << timer << "microseconds" << std::endl;
                    
                    auto start2=chrono::high_resolution_clock::now();
                    searched=myAVLTree.find(m);  //for AVL
                    auto end2=chrono::high_resolution_clock::now();
                    long long timer2 = (end2-start2).count();
                    cout << "[AVL] Elapsed time of: " << timer2 << "microseconds" << std::endl;
                    
                    cout << searched.info << endl;
                }
                else {
                    cout << "Invalid title." <<endl;
                }
                
            }
            if (choice2 == 4) { //Add a new item
                string title, descript;
                
                cout << "Enter a title for the item: ";
                cin >> title;
                cout << "Enter a description for the item: ";
                cin >> descript;
                
                content b;
                b.section=Section;
                b.title=title;
                b.info=descript;
                b.ifsection=false;
                
                if (myTree.find(b)==a) {
                 
                    auto start=chrono::high_resolution_clock::now();
                    myTree.insert(b);  //for BST
                    auto end=chrono::high_resolution_clock::now();
                    long long timer = (end-start).count();
                    cout << "[BST] Elapsed time of: " << timer << "microseconds" << std::endl;
                    
                    auto start2=chrono::high_resolution_clock::now();
                    myAVLTree.insert(b);  //for AVL
                    auto end2=chrono::high_resolution_clock::now();
                    long long timer2 = (end2-start2).count();
                    cout << "[AVL] Elapsed time of: " << timer2 << "microseconds" << std::endl;
                    
                    
                    
                    cout << "The new item " << title << " has been inserted." << endl;
                }
                else {
                    cout << "Item " << title << " already exists in the " << Section << ". "<<endl;
                }
            }
            if (choice2 == 5) { //Update the info of an item
                string itemTitle,newInfo;
                
                cout << "Enter the title of the item: ";
                cin >>itemTitle;
                cout << "Enter the new information: ";
                cin >> newInfo;
                
                content m;
                m.section=Section;
                m.title=itemTitle;
                m.ifsection=false;
                
                if (myTree.find(m)!=a) {
                    
                    auto start=chrono::high_resolution_clock::now();
                    myTree.find(m).info=newInfo; //BST
                    auto end=chrono::high_resolution_clock::now();
                    long long timer = (end-start).count();
                    cout << "[BST] Elapsed time: " << timer << "microseconds" << std::endl;
                    
                    auto start2=chrono::high_resolution_clock::now();
                    myAVLTree.find(m).info=newInfo;  //AVL
                    auto end2=chrono::high_resolution_clock::now();
                    long long timer2 = (end2-start2).count();
                    cout << "[AVL] Elapsed time: " << timer2 << "microseconds" << std::endl;
                    
                        
                    cout << "The content " << Section << " has been updated." <<endl;
                }
                else {
                    cout << "Item " << itemTitle << " does not exist."<< endl;
                }
                
            }
            if (choice2 == 6) { //Delete an item
                string itemTitle;
                
                cout << "Enter the title of the item: ";
                cin >>itemTitle;
                
                content m, searched;
                m.section=Section;
                m.title=itemTitle;
                m.ifsection=false;
                
                searched=myTree.find(m);   //return by reference gibi çalışıyor pointer type return olduğu için
                
                if (searched != a) {
                    
                    auto start2=chrono::high_resolution_clock::now();
                    myTree.remove(searched);   //BST
                    auto end2=chrono::high_resolution_clock::now();
                    long long timer2 = (end2-start2).count();
                    cout << "[BST] Elapsed time: " << timer2 << "microseconds" << std::endl;
                    
                    //myAVLTree.remove(searched);//AVL
                        
                }
                else {
                    cout << "Item " << itemTitle << " does not exist in the " << Section << "." <<endl;
                }
            }
            if (choice2 == 7) { //Back to main menu
            }
            
        }
        
        if (choice ==4 ) { //Add new section
            string newSect;
            cout << "Enter a title for the section: ";
            cin >>newSect;
            
            content newSection;
            newSection.title=newSect;
            newSection.ifsection=true;
            //section koyuyo muydum? hayır galiba
            
            if (myTree.find(newSection)==a) {
                             
                auto start=chrono::high_resolution_clock::now();
                myTree.insert(newSection);
                auto end=chrono::high_resolution_clock::now();
                long long timer = (end-start).count();
                cout << "[BST] Elapsed time: " << timer << "microseconds" << std::endl;
                
                auto start2=chrono::high_resolution_clock::now();
                myAVLTree.insert(newSection);
                auto end2=chrono::high_resolution_clock::now();
                long long timer2 = (end2-start2).count();
                
                cout << "[AVL] Elapsed time: " << timer2 << "microseconds" << std::endl;
            }
            else {
                cout << "Section " << newSect << " already exists." <<endl;
            }
        }
        
        if (choice ==5 ) { //delete a section
            string byeSect;
            // sectionu byeSect olan itemleri çıkarıp sonra byeSect i sil
            cout << "Enter the title of the section: ";
            cin >> byeSect;
            
            itemPrinter(myTree.root, byeSect); //section u byeSect olmayan her şeyi false yaptı
            sectionPrinter(myTree.root, byeSect);
           //true olması gerekenler true, şimdi silme vakti
            
            
            auto start=chrono::high_resolution_clock::now();
            travelAndRemove(myTree.root, myTree); //BST
            auto end=chrono::high_resolution_clock::now();
            long long timer = (end-start).count();
            cout << "[BST] Elapsed time: " << timer << "microseconds" << std::endl;
            
            //travelAndRemoveAVL(myAVLTree.root, myAVLTree); //AVL
            
            //her seyi tekrar true yap
            travelAndChange(myTree.root, true, true);
            travelAndChange(myTree.root, true, false);
        }
        cout << "MENU" << endl << "Please enter an input between [1 - 6]:" << endl << "1- Display the sections [AVL]" << endl << "2- Display the sections [BST]" << endl << "3- Select a section" << endl << "4- Add new section" << endl << "5- Delete a section" << endl << "6- Exit" << endl << "Input: ";
        cin >> choice;
    }
    return 0;
}
