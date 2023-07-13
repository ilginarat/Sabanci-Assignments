//  hash.h
//  ilginelif_cs300_HW3
//  Created by Ilgın Arat on 4.05.2022.

#ifndef HASH_h
#define HASH_h

#include <iostream>
#include <string>

using std::vector;


bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;
    if ( n == 1 || n % 2 == 0 )
        return false;
    for ( int i = 3; i * i <= n; i += 2 )
         if ( n % i == 0 )
             return false;
    return true;
}


int nextPrime( int n )
{
      if ( n % 2 == 0 )
          n++;
      for ( ; ! isPrime( n ); n += 2 )
           ;
      return n;
}


template <class T> class node      //constructor?
{
public:
    
    T data; //also write a struct/class for this
    node* next=NULL; //pointer to the next node element
    
    T& retrieve( )
    {
        return this->data;
    }
    
};


template <class T> class List      //constructor?
{
public:
    

    node<T>* Head=NULL; //pointer to the next node element
    
    void makeEmpty( ) {
        node<T>* head=Head;
        
        if (head!=NULL) {
            while (head->next!=NULL) {
                node<T>* temp=head;
                head=head->next;
                delete temp;
            }
            delete head;
        }
    }
    
    
    int size( )
    {
        List head=this; //bu calisir mi----------*************------------*************-----
        int counter=0;
        
        if (head!=NULL) {
            counter++;
            while (head->next!=NULL) {
                head=head->next;
                counter++;
            }
        }
        return counter;
    }
    
    
    node<T>* find ( T x)
    {     //pointer yerine adress koysam ne değişirdi?
        
        List<T> linkedList=*this;
        node<T>* head=linkedList.Head;
        
        while (head!=NULL) {
            
            if (head->data == x) {
                return head;
            }
            head=head->next;
        }
        return NULL;
    }
    
    
    node<T>* zeroth ( )
    {
        node<T>* newNode= new node<T>;
        
        if (Head==NULL) {
            Head=newNode;
        }
        else {
            newNode->next=Head;
            Head=newNode;
        }
        return Head;
    }
    
    
    void insert(  T & x, node<T>* myNode )
    {
        myNode->data=x; //SIMDI CIGLIK ATICAM
    }
    
    
    void remove( const T x);
    
    List<T> operator=(List<T>& rhs) //basta & olmayacak dimi??
    {
        
        List<T> myList;
        node<T>* myHead=myList.Head;
        node<T>* oldHead=rhs.Head;
        
        while(oldHead!=NULL) {
            myHead=oldHead;
            myHead=myHead->next;
            oldHead=oldHead->next;
        }
        
        return myList;
    }
    
};


template <class HashedObj>
    class HashTable
    {
      public:
        HashTable( const HashedObj & notFound, int size = 53 ): ITEM_NOT_FOUND( notFound ), theLists( nextPrime( size ) )
        {
        };
        
        HashTable( const HashTable & rhs )                      //copy constructor?
                : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                                 theLists( rhs.theLists ) { }

        

        int size ( ){
            return theLists.size();
        }
        
         HashedObj & find(  HashedObj & x )
        {
              node<HashedObj>* itr;
              // locate the approriate list and search there
              itr = theLists[ x.hash(theLists.size()) ].find( x );
              // retrieve from the located position
              if ( itr==NULL )
                 return ITEM_NOT_FOUND;

            return itr->retrieve( );
        }
        

        void makeEmpty( )
        {
            for( int i = 0; i < theLists.size( ); i++ )
                theLists[ i ].makeEmpty( );
                    // destroy the lists but not the vector!
        }
        
        
        void insert(  HashedObj & x )
        {
           // hash the given object and locate the list it should be on
           List<HashedObj> & whichList = theLists[ x.hash( theLists.size( ) ) ];   //linked list burada (oluşturuyo muyum????)--&ne işe yarıyo
           // locate the object in the list (using List’s find)
           node<HashedObj>*itr = whichList.find( x );
           // insert the new item at the head of the list if not found!
           if ( itr==NULL ) //if not exist
               
                whichList.insert( x, whichList.zeroth( ) );
        }
        
        
        void remove( const HashedObj & x )
        {
           // remove from the appropriate list
           theLists[ x.hash( theLists.size( ) ) ].remove( x );
        }
        

        const HashTable & operator=( const HashTable & rhs)    //copy constructor?
        { //deep copy mi
            
            this->theLists=rhs.theLists;    //linked listler shallow copy mi oldu noldu??
            return *this;
        }
        
        
        vector<List<HashedObj>> returnList( )
        {
            return theLists;
        }

    private:
        vector<List<HashedObj>> theLists; // The array of Lists
         HashedObj ITEM_NOT_FOUND;
    };

#endif

