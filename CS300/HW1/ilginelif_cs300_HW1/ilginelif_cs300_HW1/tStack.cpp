//  tStack.cpp
//  ilginelif_cs300_HW1
//
//  Created by Ilgın Arat on 22.03.2022.
//

#include "tStack.h"
#include <string>
#include <iostream>

using namespace std;

template <class Object>
    Stack<Object>::Stack( )
    {
      topOfStack = NULL;
    }

template <class Object>
    bool Stack<Object>::isFull( ) const
    {
        return false;
    }

template <class Object>
    bool Stack<Object>::isEmpty( ) const
    {
        return topOfStack == NULL;
    }

template <class Object>
     ListNode<Object>*  Stack<Object>::top()
    {
        if ( isEmpty()) {
            return nullptr;
        }
         return topOfStack;
    }

template <class Object>
    void Stack<Object>::pop( ) //what does this const do here??
    {
        if ( isEmpty( ) ) {
            cout << "nothing to pop" <<endl;
        }
        ListNode<Object> *oldTop = topOfStack;
        topOfStack = topOfStack->next;
        delete oldTop;
    }

template <class Object>
    void Stack<Object>::push( const Object& value )
    {
        topOfStack = new ListNode<Object>( value, topOfStack ); //should I put <Object> here??
    }

template <class Object>
    Object Stack<Object>::topAndPop( )
    {
         Object topItem = top( )->value;
         pop( );
         return topItem;
    }

template <class Object>
    void Stack<Object>::makeEmpty( )
    {
        while ( ! isEmpty( ) )
             pop( );
    }

template <class Object>
    const Stack<Object> & Stack<Object>::operator=( const Stack<Object> & rhs )
    {
          if ( this != &rhs )
          {
               makeEmpty( );
               if ( rhs.isEmpty( ) )
                    return *this;

               ListNode<Object> *rptr = rhs.topOfStack;
               ListNode<Object> *ptr  = new ListNode( rptr->element );
               topOfStack = ptr;

               for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
                     ptr = ptr->next = new ListNode( rptr->element );
        }
        return *this;
    }

template <class Object>
    Stack<Object>::~Stack( )
    {
          makeEmpty( );
    }
