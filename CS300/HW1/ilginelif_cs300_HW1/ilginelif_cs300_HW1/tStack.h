//  tStack.h
//  ilginelif_cs300_HW1
//
//  Created by Ilgın Arat on 22.03.2022.

#ifndef tStack_h
#define tStack_h
#include <iostream>
#include <string>
using namespace std;

template <class Object>  //why the main.cpp doesnt recognise the struct when
    struct ListNode      //I put the struct in the class' public???
    {
        Object value;
        ListNode *next;  //burda koymadıysam
        ListNode(Object val, ListNode<Object>* N=NULL):value(val), next(N) {}  //burda neden <> koydum?
    };

template <class Object>
    class Stack
    {
      public:
        
        Stack( );
        Stack( const Stack & rhs );
        ~Stack( );

        bool isEmpty( ) const;
        bool isFull( ) const;
        void makeEmpty( );

        void pop( );
        void push(const Object &value); 
        Object topAndPop( );
         ListNode<Object>* top();

        const Stack & operator=( const Stack & rhs );

      private:
        ListNode<Object> *topOfStack;  // list itself is the stack  burda da koymusum
    };

#endif /* tStack_h */
