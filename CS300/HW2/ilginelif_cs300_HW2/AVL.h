//  Created by Ilgın Arat on 11.04.2022.
//

#ifndef AVL_h
#define AVL_h

#include <iostream>
#include <string>
using namespace std;

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
public:
       Comparable element;
       AvlNode *left;
       AvlNode *right;
        int  height;
    
        void suitable(bool x); //gerek kalmadi ama olsun
        bool ifSuitable;

       AvlNode( const Comparable & theElement,
                  AvlNode *lt, AvlNode *rt, int h = 0 )
            : element( theElement ), left( lt ), right( rt ), height( h ) {
                ifSuitable=true;
            }

      friend class AvlTree<Comparable>;
};


template <class Comparable>
class AvlTree
{
     public:
        AvlNode<Comparable> *root;
    
        explicit AvlTree( const Comparable & notFound );
        AvlTree( const AvlTree & rhs );
       ~AvlTree( );

        const Comparable & findMin( ) const;
        const Comparable & findMax( ) const;
         Comparable & find(  Comparable & x ) ;
        bool isEmpty( ) const;
        void printTree( ) const;

        void makeEmpty( );
        void insert(  Comparable & x );
        void remove(  Comparable & x );

        const AvlTree & operator=( const AvlTree & rhs );

    private: //doğru yerde mi??
         
          Comparable ITEM_NOT_FOUND;
          Comparable & elementAt( AvlNode<Comparable> *t ) ;

         void insert(  Comparable & x, AvlNode<Comparable> * & t ) const;
         void remove( Comparable & x, AvlNode<Comparable> * & t ) const;

         AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
         AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
         AvlNode<Comparable> * find(  Comparable & x, AvlNode<Comparable> *t ) const;
         void makeEmpty( AvlNode<Comparable> * & t ) const;
         void printTree( AvlNode<Comparable> *t ) const;
         AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;

         // Avl manipulations
         int height( AvlNode<Comparable> *t ) const;
         int max( int lhs, int rhs ) const;
         void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
         void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
         void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
         void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
};

#endif /* AVL_h */
