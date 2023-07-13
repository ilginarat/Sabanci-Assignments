//  main.cpp
//  ilginelif_cs300_HW3
//
//  Created by Ilgın Arat on 4.05.2022.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include "BST.h"
#include "BST.cpp"
#include "hash.h"

using std::string, std::vector;

struct DocumentItem {
    string documentName;
    int count;
    
    DocumentItem operator = (DocumentItem & x) {

        DocumentItem newItem;
        newItem.documentName=x.documentName;
        newItem.count=x.count;
        
        return newItem;
    }
    
};

struct WordItem {
    string word;
    vector <DocumentItem> docList;
    
    
    bool operator == (WordItem & x) {
        if (word==x.word) {
            return true;
        }
        else return false;
    }
    
    bool operator < (WordItem & x) {
        if (word < x.word ) {   //alphebetical order
            return true;
        }
        else {
            return false;
        }
    }
    
    bool operator > (WordItem & x) {
        if (word > x.word) {
            return true;
        }
        else {
            return false;
        }
    }
    
    WordItem& operator = (WordItem & x) {

        this->word=x.word;
        this->docList=x.docList;
        
        return *this; //new item mi shallow copy oluyo
    }
    
    
    int hash (const string & key, int tableSize)               //string
    {
          int sum = 0;
          for (int i = 0; i < key.length(); i++) // add all bytes in a loop
               sum = sum + key[ i ];
          return (sum % tableSize);
    }
    
    
    int hash(int tableSize ) {
        
        return hash(word, tableSize);
        
    }
};


int main() {
    
    int num;
    
    cout << "Enter number of input files: ";
    cin >> num;
    int counter=0;
    
    WordItem a;
    a.word="";
    
    const WordItem ITEM_NOT_FOUND = a;
    BinarySearchTree<WordItem> myTree(a);
    HashTable<WordItem> myHash(a);
    
    int itemCount=0;
    double loadFactor;
    
    vector<string> wordVec; //to keep the words
    vector<string> fileVec;
    
    while (counter < num) {
        counter++;
        string line, fileName;
        
        cout << "Enter "<< counter << ". file name: ";
        cin >> fileName;
        
        fileVec.push_back(fileName);
        
        ifstream myFile;
        myFile.open(fileName.c_str());
        
        
        wordVec.clear();
        
        // To CREATE
        
        while (getline(myFile, line)) {
            
            string myWord=line;
            ToLower(myWord);
            
            int ind=0, howMany;
            string nWord;
            
            for (int i=0; i < myWord.length(); i++) {
                
                if (myWord[i] < 97 || myWord[i] > 122) {
                    howMany=i-ind;
                    nWord=myWord.substr(ind, howMany );
                    if (nWord!="") {
                        wordVec.push_back(nWord);
                    }
                    ind=i+1;
                }
            }
            howMany=myWord.length()-ind;
            nWord=myWord.substr(ind, howMany );
            if (nWord!="") {
                wordVec.push_back(nWord);
            }
        }
            
        for (int j=0; j < wordVec.size(); j++) {
            
            // for BST
            WordItem theWord;
            theWord.word=wordVec[j];
            WordItem* ptr;
            
            ptr = &myTree.find(theWord);
            
            
            if (*ptr == a) {            // kelime yoksa
                DocumentItem docItem;
                docItem.documentName=fileName;
                docItem.count=1;
                theWord.docList.push_back(docItem);
                myTree.insert(theWord);
            }
            else {
                bool ifExist=false;     // to check if its in this file
                
                for (int j=0; j<ptr->docList.size(); j++) {
                    
                    if (ptr->docList[j].documentName==fileName) {
                        ptr->docList[j].count++;
                        ifExist=true;
                    }
                }
                if (!(ifExist)) {
                    
                    DocumentItem docitem;
                    docitem.count=1;
                    docitem.documentName=fileName;
                    ptr->docList.push_back(docitem);
                }
            }
            
            
            // for HashTable
            
            WordItem theWordHash;
            theWordHash.word=wordVec[j];
            
            ptr = &myHash.find(theWordHash);
            //int index= myHash.hash( myWord, myHash.size());
            
            if (*ptr==a) { //linked list de yok insert edicez
                
                DocumentItem docItem;
                docItem.documentName=fileName;
                docItem.count=1;
                theWordHash.docList.push_back(docItem);
                myHash.insert(theWordHash);
                
                itemCount++;
                loadFactor= (double) itemCount /myHash.size();
                
                if (loadFactor >= 0.9) {    //REHASHING*-*-*-*-*-*-*-*-*-*
                    
                    cout << "rehashed..." << endl;
                    cout << "previous table size:" << myHash.size();
                    
                    
                    HashTable newHash = HashTable( a, 2*myHash.size());
                    
                    for (int i=0; i < myHash.size(); i++) {
                        
                        List<WordItem> myList=myHash.returnList()[i];
                        
                        node<WordItem>* head=myList.Head;
                        
                        while ( head != NULL ) {
                            
                            newHash.insert(head->data);
                            head=head->next;
                        }
                    }
                    myHash.makeEmpty();
                    myHash=newHash;         //hash copy constructor---memory israfı değil mi??????????
                    
                    loadFactor= (double) itemCount/myHash.size();
                    
                    cout << ", new table size: " << myHash.size() << ", current unique word count: " << itemCount+1 << ",current load factor: " << loadFactor << endl;
                    
                }
            }
            else {  //linked list de var
                
                bool ifExist=false;     // to check if its in this file
                
                for (int j=0; j<ptr->docList.size(); j++) {
                    
                    if (ptr->docList[j].documentName==fileName) {
                        ptr->docList[j].count++;
                        ifExist=true;
                    }
                }
                if (!(ifExist)) {
                    
                    DocumentItem docitem;
                    docitem.count=1;
                    docitem.documentName=fileName;
                    ptr->docList.push_back(docitem);
                }
            }
        }
        
        loadFactor= (double) itemCount/myHash.size();
        cout << endl << endl << "After preprocessing, the unique word count is " << itemCount << ". Current load ratio is " << loadFactor <<endl<< endl;
    }
    
    
    //  Query Part
    
    string query, each;
    cout << "Enter queried words in one line: ";
    cin >> query;
    cout << endl;
    vector <string> myVec;
    istringstream s (query);
    
    // bakılacak bütün kelimeler myVec'de
    while (s >> each) {
        
        ToLower(each);
        int index=0, many;
        string newWord;
        
        for (int i=0; i < each.length(); i++) {
            
            if (each[i] < 97 || each[i] > 122) {
                many=i-index;
                newWord= each.substr(index,many);
                myVec.push_back(newWord);
                index=i+1;
            }
        }
        many=each.length()-index;
        newWord=each.substr(index,many);
        myVec.push_back(newWord);
    }
    
//    for BST
    
    double bstT,hashT;
    
    for (int i=0; i < fileVec.size(); i++) {    // her txt file için
        cout << "In document " << fileVec[i];
        WordItem* itself;
        
        for (int j=0; j < myVec.size(); j++) {  //her kelime
            
            WordItem m;
            m.word=myVec[j];
            
            
            int k = 20;
             auto start = std::chrono::high_resolution_clock::now();
             for (int i = 0; i < k; i++)
             {
                 
                 itself=&myTree.find(m);
                 
             }
             auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
                                     (std::chrono::high_resolution_clock::now() -
                               start);
        
            bstT=BSTTime.count() / k;
            
            for (int l=0; l < itself->docList.size(); l++) {
                
                if (itself->docList[l].documentName==fileVec[i]) {
                    
                    cout << ", " << itself->word << " found " << itself->docList[l].count << " times";
                }
            }
        }
        cout << "." <<endl;
    }
    
    

//    for HashTable

    for (int i=0; i < fileVec.size(); i++) {    // her txt file için
        cout << "In document " << fileVec[i];
        WordItem* itself;
        
        for (int j=0; j < myVec.size(); j++) {  //her kelime
            
            WordItem m;
            m.word=myVec[j];
            
            int k=20;
            auto start = std::chrono::high_resolution_clock::now();
              for (int i = 0; i < k; i++)
              {
                  
                  itself=&myHash.find(m);
                  
              }
              auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
                                (std::chrono::high_resolution_clock::now() - start);
            
            hashT=HTTime.count() / k;
            
            
            for (int l=0; l < itself->docList.size(); l++) {
                
                if (itself->docList[l].documentName==fileVec[i]) {
                    
                    cout << ", " << itself->word << " found " << itself->docList[l].count << " times";
                }
            }
        }
        cout << "." <<endl;
    }
    
    
    
    cout << "\nTime: " << bstT << "\n";
    cout << "\nTime: " << hashT << "\n";
    cout << "\nSpeed Up: " << bstT / hashT;

    return 0;
}
