//  Created by Ilgın Arat on 11.04.2022.
//
#include <chrono>
#include "AVL.h"
#include "BST.h"
#include <iostream>
#include <string>
using namespace std;



template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t )
const
 {
        if (t == NULL)
           return -1;
    
      return t->height;
}

template <class Comparable>
void AvlNode<Comparable>::suitable(bool x)
{
    ifSuitable=x;
}


template <class Comparable>
AvlTree<Comparable>::                              //constructor
AvlTree(const Comparable & notFound ) :ITEM_NOT_FOUND( notFound ), root( NULL )
{
}


template <class Comparable>
AvlTree<Comparable>::~AvlTree( )          //destructor
{
    makeEmpty( );
}


template <class Comparable>
AvlTree<Comparable>::
AvlTree( const AvlTree<Comparable> & rhs ) :      //copy constructor
      root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}


template <class Comparable>
 Comparable & AvlTree<Comparable>::
find(  Comparable & x )
{
     return elementAt( find( x, root ) );
}


template <class Comparable>
const Comparable & AvlTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}


template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}


template <class Comparable>
void AvlTree<Comparable>::insert(  Comparable & x )
{
    insert( x, root );
}


template <class Comparable>
void AvlTree<Comparable>::remove
                  (  Comparable & x )
{
       remove( x, root );
}


template <class Comparable>
      void AvlTree<Comparable>::makeEmpty( )
      {
           makeEmpty( root );
      }


template <class Comparable>
void AvlTree<Comparable>::printTree( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}


//  PRIVATE MEMBER FUNCTIONS


template <class Comparable>
 Comparable & AvlTree<Comparable>::
elementAt( AvlNode<Comparable> *t )
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::
find(  Comparable & x, AvlNode<Comparable> * t ) const
{
     if ( t == NULL )
          return NULL;
     else if( x < t->element )
          return find( x, t->left );
     else if( t->element < x )
          return find( x, t->right );
     else
          return t;    // Match
}

template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}


template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::findMax( AvlNode<Comparable> *t ) const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}


template <class Comparable>
 void AvlTree<Comparable>::insert ( Comparable & x, AvlNode<Comparable> * & t ) const
 {
     if ( t == NULL ) {
           t = new AvlNode<Comparable>( x, NULL, NULL );
     }
      else if ( x < t->element ) {
           // X should be inserted to the left tree!
           insert( x, t->left );
           
          // Check if the left tree is out of balance (left subtree grew in height!)
          if ( height( t->left ) - height( t->right ) == 2 ) {
               if ( x < t->left->element ) { // X was inserted to the left-left subtree!
                     rotateWithLeftChild( t );
               }
                else {                 // X was inserted to the left-right subtree!
                     doubleWithLeftChild( t );
                }
          }
       }
      else if( t->element < x )
      {    // Otherwise X is inserted to the right subtree
            insert( x, t->right );
          if ( height( t->right ) - height( t->left ) == 2 ) {
       // height of the right subtree increased
              if ( t->right->element < x ) {
                    // X was inserted to right-right subtree
                       rotateWithRightChild( t );
              }
              else {// X was inserted to right-left subtree
                      doubleWithRightChild( t );
              }
          }
       }
       else
           ;  // Duplicate; do nothing
       
     // update the height the node
       t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::remove(  Comparable & x, AvlNode<Comparable> * & t ) const // x tree de olduğu zaman çalışıyo
{
    if( t == NULL )
        return;   // Item not found; do nothing
                                                           //x yoksa siciyoruz
    if (x != t->element) {
    
        if( x < t->element )
            remove( x, t->left );
        
        else if( t->element < x )
            remove( x, t->right );
        
        if (t!=NULL) {
            t->height=max(height(t->left),height(t->right))+1;
        }
    }
    else {
    
        if( t->left != NULL && t->right != NULL ) // Two children
       {
           if (t->ifSuitable==true) {
               t->element = findMin( t->right )->element;
               remove( t->element, t->right );
           }
           if (t!=NULL) {
               t->height=max(height(t->left),height(t->right))+1;
           }
       }
        
        else // one or no children
        {
            AvlNode<Comparable> *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            
            if (t!=NULL) {
                t->height=max(height(t->left),height(t->right))+1;  //bunun yeri doğru mu ya
            }
            if (oldNode->ifSuitable==true) {
                delete oldNode;
            }
        }
    }
       // t yi düzenlemem lazım ama nasıl--------***********----------***********----------***********----------**********
    if (t!=NULL && t->right!=NULL && t->left != NULL) {
        if ( height( t->left ) - height( t->right ) == 2 ) {
             if ( x < t->left->element ) { // X was inserted to the left-left subtree!
                 
                 if (t->left !=NULL && t->left->right!=NULL) {
                   rotateWithLeftChild( t );
                 }
             }
              else {                 // X was inserted to the left-right subtree!
                   doubleWithLeftChild( t );
              }
        }
        else if ( height( t->right ) - height( t->left ) == 2 ) {
            // height of the right subtree increased
            if ( t->right->element < x ) {
                  // X was inserted to right-right subtree
                     rotateWithRightChild( t );
            }
            else {// X was inserted to right-left subtree
                    doubleWithRightChild( t );
            }
        }
//        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
}


template <class Comparable>
void AvlTree<Comparable>::
makeEmpty( AvlNode<Comparable> * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}


template <class Comparable>
void AvlTree<Comparable>::
     printTree( AvlNode<Comparable> * t ) const
{
      if ( t != NULL )
      {
            printTree( t->left );
            if (t->ifSuitable== true) {
              cout << t->element << endl;
            }
            printTree( t->right );
      }
}


template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::
   clone( AvlNode<Comparable> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new AvlNode<Comparable>
            ( t->element,
              clone( t->left ),
              clone( t->right ) );
}


template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const
{
      if (lhs > rhs)
          return lhs;

      return rhs;
}


template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable> * & k2 ) const
{
       AvlNode<Comparable> *k1 = k2->left;
       k2->left = k1->right;
       k1->right = k2;
       k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
       k1->height = max( height( k1->left ), k2->height ) + 1;
       k2 = k1;
}


template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild ( AvlNode<Comparable> * & k1 ) const
{
      AvlNode<Comparable> *k2 = k1->right;
      k1->right = k2->left;
      k2->left = k1;
      k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
      k2->height = max( height( k2->right ), k1->height ) + 1;
      k1 = k2;
}


template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild
        ( AvlNode<Comparable> * & k3 ) const
{
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
}


template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild
        ( AvlNode<Comparable> * & k1 ) const
{
       rotateWithLeftChild( k1->right );
       rotateWithRightChild( k1 );
}
