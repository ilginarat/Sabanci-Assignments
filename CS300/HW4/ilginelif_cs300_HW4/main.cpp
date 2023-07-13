//  main.cpp
//  ilginelif_cs300_HW4
//
//  Created by Ilgın Arat on 24.05.2022.


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Sort.h"
using namespace std;

struct phoneBook {
    
    string name;
    string surname;
    string phone;
    string city;
    
    bool operator < (phoneBook & x) {
        if (name < x.name ) {   //alphebetical order
            return true;
        }
        else if (name==x.name) {
            if (surname < x.surname) return true;
            else return false;
        }
        else {
            return false;
        }
    }
    
    bool operator > (phoneBook & x) {
        if (name > x.name) {
            return true;
        }
        else if (name==x.name) {
            if (surname > x.surname) return true;
            else return false;
        }
        else {
            return false;
        }
    }
    
    bool operator <= (phoneBook & x) {
        if (name > x.name ) {
            return false;
        }
        else {
            return true;
        }
    }
    
    bool operator == (phoneBook & x) {
        if (name == x.name && surname==x.surname) {
            return true;
        }
        else {
            return false;
        }
    }
};


bool ifInString (string b, string a) { // if a is in b
    
    for (int i=0; i < a.length(); i++) {
        
        if (a[i]!=b[i]) {
            return false;
        }
    }
    return true;
}


int bsearch( vector<phoneBook> & list, phoneBook & key) {

    int low = 0;
    int high = list.size()-1;
    int mid;
    while (low <= high) {
        mid = (low + high)/2;
        if (list[mid] == key)  // found
            return mid;
        else if (list[mid] < key) //upper
            low = mid + 1;
        else // key in lower half
            high = mid - 1;
    }
    return -1; // not in list
}


int partialBSearch( vector<phoneBook> & list, phoneBook & key) {

    int low = 0;
    int high = list.size()-1;
    int mid;
    while (low <= high) {
        mid = (low + high)/2;
        if (ifInString(list[mid].name, key.name))  // found
            return mid;
        else if (list[mid] < key) //upper
            low = mid + 1;
        else // key in lower half
            high = mid - 1;
    }
    return -1; // not in list
}


int main() {

    string line, fileName, input, name, surname="";
    vector<phoneBook> insertionVec, quickVec, mergeVec, heapVec;
    double seq, bin;
    
    cout << "Please enter the contact file name: ";
    cin >> fileName;
    
    ifstream myFile;
    myFile.open(fileName.c_str());
    
    cin.ignore();
    cout << "Please enter the word to be queried : ";
    getline(cin, input);
    
    while (getline(myFile, line)) {
        
        istringstream ss(line);
        phoneBook each;
        ss >> each.name >> each.surname >> each.phone >> each.city;
        
        insertionVec.push_back(each);
        quickVec.push_back(each);
        mergeVec.push_back(each);
        heapVec.push_back(each);
    }
    
    istringstream myInput(input);
    myInput >> name >> surname;     // ok mu?
    
    cout << endl <<"Sorting the vector copies" << endl << "======================================" << endl;
    
    
    int k = 100;
      auto start1 = std::chrono::high_resolution_clock::now();
      for (int i = 0; i < k; i++)
      {
          insertionSort(insertionVec);
      }
      auto insertT = std::chrono::duration_cast<std::chrono::nanoseconds>
                        (std::chrono::high_resolution_clock::now() - start1);
      cout << "Insertion Sort Time: " << insertT.count() / k << " Nanoseconds" << endl;
    
    
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        quicksort(quickVec);
    }
    auto quickT = std::chrono::duration_cast<std::chrono::nanoseconds>
                      (std::chrono::high_resolution_clock::now() - start2);
    cout << "Insertion Sort Time: " << quickT.count() / k << " Nanoseconds" << endl;
    
    
    auto start3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        mergeSort(mergeVec);
    }
    auto mergeT = std::chrono::duration_cast<std::chrono::nanoseconds>
                      (std::chrono::high_resolution_clock::now() - start3);
    cout << "Insertion Sort Time: " << mergeT.count() / k << " Nanoseconds" << endl;
    
    
    
    auto start4 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        heapsort(heapVec);
    }
    auto heapT = std::chrono::duration_cast<std::chrono::nanoseconds>
                      (std::chrono::high_resolution_clock::now() - start4);
    cout << "Insertion Sort Time: " << heapT.count() / k << " Nanoseconds" << endl;
    
    
    cout << endl << endl << "Searching for " << name << " " << surname << endl << "======================================" << endl;
    
    if (surname == "") { //partial
        
        // sequental search
        
        
      auto start5 = std::chrono::high_resolution_clock::now();
      vector <int> myIndex;
      for (int i = 0; i < k; i++)
      {
          
          bool ifFound=false;
          
          for (int i=0; i < insertionVec.size(); i++) {
              
              bool ifMatch=true;
              for (int j=0; j< name.length(); j++) {
                  
                  if (name[j] != insertionVec[i].name[j]) {
                      ifMatch=false;
                      break;
                  }
              }
              
              if (ifMatch) {
                  ifFound=true;
                  
                  bool ifIIn=false;
                  for (int m=0; m < myIndex.size(); m++) {
                      if (myIndex[m]==i) {
                          ifIIn=true;
                      }
                  }
                  
                  if (ifIIn==false) {
                      myIndex.push_back(i);
                  }
              }
          }
          
      }
      auto partSeq = std::chrono::duration_cast<std::chrono::nanoseconds>
                        (std::chrono::high_resolution_clock::now() - start5);
        
        for (int i=0; i < myIndex.size(); i++) {
            
            cout << insertionVec[myIndex[i]].name << " " << insertionVec[myIndex[i]].surname << " " << insertionVec[myIndex[i]].phone << " " << insertionVec[myIndex[i]].city << endl;
        }
        if (myIndex.size()==0) {
            cout << name << " does NOT exist in the dataset" << endl;
        }
      cout  << "Sequental Search Time: " << partSeq.count() / k  << " Nanoseconds " << endl << endl;
        seq=partSeq.count() / k ;
             

        
        // binary search
        
        
      auto start6 = std::chrono::high_resolution_clock::now();
      vector <int> myIndexes;
      for (int i = 0; i < k; i++)
      {
            
          phoneBook searched;
          searched.name=name;
      
          int index= partialBSearch(insertionVec, searched); //içinde geçen herhangi birinin indexini return ediyo
   
          for (int b=index-1 ; ifInString(insertionVec[b].name, name) ; b--) {
              
              index--;
          }
          
          for (int b=index ; ifInString(insertionVec[b].name, name) ; b++) {
              
              bool ifBIn=false;
              for (int n=0; n < myIndexes.size(); n++) {
                  if (myIndexes[n]==b) {
                      ifBIn=true;
                  }
              }
              
              if (ifBIn==false) {
                  myIndexes.push_back(b);
              }
          }
          
      }
      auto partBin = std::chrono::duration_cast<std::chrono::nanoseconds>
                        (std::chrono::high_resolution_clock::now() - start6);
        
        for (int i=0; i < myIndexes.size(); i++) {
            
            cout << insertionVec[myIndexes[i]].name << " " << insertionVec[myIndexes[i]].surname << " " << insertionVec[myIndexes[i]].phone << " " << insertionVec[myIndexes[i]].city << endl;
        }
        
        if (myIndexes.size()==0) {
            cout << name << " does NOT exist in the dataset" << endl;
        }
      cout << "Binary Search Time: " << partBin.count() / k << " Nanoseconds" << endl << endl;
        bin=partBin.count() / k;

    }
    
    else {  //full name
        
        // sequental search
        
        
        auto start7 = std::chrono::high_resolution_clock::now();
        vector <int> indexes;
          for (int j = 0; j < k; j++)
          {
                
              bool ifFound=false;
              for (int i=0; i < insertionVec.size(); i++) {
                  
                  if (name == insertionVec[i].name && surname == insertionVec[i].surname) {
                      ifFound=true;
                      
                      bool ifIIn=false;
                      for (int m=0; m < indexes.size(); m++) {
                          if (indexes[m]==i) {
                              ifIIn=true;
                          }
                      }
                      
                      if (ifIIn==false) {
                          indexes.push_back(i);
                      }
                  }
              }
              
          }
          auto fullSeq = std::chrono::duration_cast<std::chrono::nanoseconds>
                            (std::chrono::high_resolution_clock::now() - start7);
        
            for (int a=0; a < indexes.size(); a++) {
                cout << insertionVec[indexes[a]].name << " " << insertionVec[indexes[a]].surname << " " << insertionVec[indexes[a]].phone << " " << insertionVec[indexes[a]].city << endl;
            }
            if (indexes.size()==0) {
                cout << name << " " << surname << " does NOT exist in the dataset" << endl;
            }
            cout << "Sequental Search Time: " << fullSeq.count() / k << " Nanoseconds" << endl << endl;
            seq=fullSeq.count() / k;

        
        // binary search
        
        
        auto start8 = std::chrono::high_resolution_clock::now();
        int index = -1;
              for (int i = 0; i < k; i++)
              {
                    
                  phoneBook searched;
                  searched.name=name;
                  searched.surname=surname;
              
                  index= bsearch(insertionVec, searched);
                  
              }
              auto fullBin = std::chrono::duration_cast<std::chrono::nanoseconds>
                                (std::chrono::high_resolution_clock::now() - start8);
        
        if ( index!=-1) {
            cout << insertionVec[index].name << " " << insertionVec[index].surname << " " << insertionVec[index].phone << " " << insertionVec[index].city << endl;
        }
        else {
            cout << name << " " << surname << " does NOT exist in the dataset" << endl;
        }
              cout << "Binary Search Time : " << fullBin.count() / k << " Nanoseconds" << endl;
            bin=fullBin.count() / k ;
        
    }
    
    cout << "SpeedUp between Search Algorithms" << endl << "======================================" << endl;
    
    double speedUp=seq/bin;
    cout << "(Sequential Search/ Binary Search) SpeedUp = " << speedUp << endl << endl;
    
    
    cout << "SpeedUps between Sorting Algorithms" << endl << "======================================" << endl;
    
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << (double) insertT.count() / quickT.count() << endl;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << (double) mergeT.count() / quickT.count() << endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << (double) heapT.count() / quickT.count() << endl;
    
    return 0;
}

