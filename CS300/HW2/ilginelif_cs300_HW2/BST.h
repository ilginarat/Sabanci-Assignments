//  Created by Ilgın Arat on 8.04.2022.
//

#ifndef BST_h
#define BST_h
#include <iostream>
using namespace std;

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
public:
      Comparable element;
      BinaryNode  *left;
      BinaryNode  *right;
      void suitable(bool x);
      bool ifSuitable;

      BinaryNode( const Comparable & theElement,
                  BinaryNode *lt=NULL, BinaryNode *rt=NULL ) //null ları ben ekledim
                   : element( theElement ), left( lt ), right( rt ) {
                       ifSuitable=true; //***
                   }
    
friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
  public:
    BinaryNode<Comparable> *root;
    
     explicit BinarySearchTree( const Comparable & notFound ); // bu ne?
     BinarySearchTree( const BinarySearchTree & rhs );
     ~BinarySearchTree( );

     const Comparable & findMin( ) const;
     const Comparable & findMax( ) const;
      Comparable & find( Comparable & x ) ;
     bool isEmpty( ) const;
     void printTree( ) const;

     void makeEmpty( );
     void insert( Comparable & x );
     void remove(  Comparable & x );

     const BinarySearchTree & operator=( const BinarySearchTree & rhs );
    
private:
        Comparable ITEM_NOT_FOUND;

        Comparable & elementAt( BinaryNode<Comparable> *t ) ;

       void insert( Comparable & x, BinaryNode<Comparable> * & t ) const;
       void remove(  Comparable & x, BinaryNode<Comparable> * & t ) const;
       BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
       BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
        BinaryNode<Comparable> * find( Comparable & x, BinaryNode<Comparable> *t ) const;
       void makeEmpty( BinaryNode<Comparable> * & t ) const;
       void printTree( BinaryNode<Comparable> *t ) const;
       BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
};

#endif /* BST_h */
