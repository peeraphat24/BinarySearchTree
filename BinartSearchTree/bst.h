//
//  bst.h
//  BinartSearchTree
//
//  Created by Peeraphat Komolruchinonth on 31/3/19.
//  Copyright © 2019 Peeraphat Komolruchinonth. All rights reserved.
//

#ifndef bst_h
#define bst_h
#include <iostream>
template<class Comperable>
class BinarySearchTree;

template<class Comperable>
class BinaryNode
{
    Comperable element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode( const Comperable & theElement, BinaryNode *lt, BinaryNode *rt ) : element( theElement ), left( lt ), right( rt ){}
    friend class BinarySearchTree<Comperable>;
};

template <class Comperable>
class BinarySearchTree{
public:
    explicit BinarySearchTree( const Comperable & notFound);
    BinarySearchTree( const BinarySearchTree & rhs);
    BinarySearchTree();
    ~BinarySearchTree();
    
    const Comperable & findMin() const;
    const Comperable & findMax() const;
    const Comperable & find( const Comperable & x) const;
    const Comperable & findChild( const Comperable & x) const;
    bool isEmpty() const;
    void printTree(char c) const;
    
    void makeEmpty();
    void insert( const Comperable & x);
    void remove( const Comperable & x);
    
    const BinarySearchTree & operator=( const BinarySearchTree & rhs);
    
private:
    BinaryNode<Comperable> *root;
    const Comperable ITEM_NOT_FOUND;
    
    const Comperable & elementAt( BinaryNode<Comperable> *t) const;
    
    void insert( const Comperable & x, BinaryNode<Comperable> * &t ) const;
    void remove( const Comperable & x, BinaryNode<Comperable> * &t ) const;
    BinaryNode<Comperable> * findMin( BinaryNode<Comperable> * t ) const;
    BinaryNode<Comperable> * findMax( BinaryNode<Comperable> * t ) const;
    BinaryNode<Comperable> * find(const Comperable & x, BinaryNode<Comperable> * t ) const;
    void makeEmpty( BinaryNode<Comperable> * & t) const;
    void printTreePre( BinaryNode<Comperable> *t ) const;
    void printTreeIn( BinaryNode<Comperable> *t ) const;
    void printTreePost( BinaryNode<Comperable> *t ) const;
    BinaryNode<Comperable> * clone( BinaryNode<Comperable> *t ) const;
};

//////////////////////////////////////////////////////////////////////
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const Comparable & notFound ) : root( NULL ), ITEM_NOT_FOUND( notFound )
{
}

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( ) :
root( NULL ), ITEM_NOT_FOUND( Comparable() )
{
}

template <class Comperable>
const Comperable & BinarySearchTree<Comperable>::elementAt( BinaryNode<Comperable> *t) const
{
    return  t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comperable>
const Comperable & BinarySearchTree<Comperable>::find( const Comperable & x) const
{
    return elementAt( find(x, root));
}
template <class Comperable>
const Comperable & BinarySearchTree<Comperable>::findChild( const Comperable & x) const
{
    if(find(x, root)!=NULL) cout<<"\nFOUND MEMORY OF CHILD IS "<<find(x, root)<<"\n\n";
    return elementAt( find(x, root));
}

template <class Comperable>
const Comperable & BinarySearchTree<Comperable>::findMin() const
{
    if(findMin(root)!=NULL) cout<<"\nMIN ELEMENT OF TREE IS "<<elementAt(findMin(root))<<"\n\nMEMORY OF CHILD IS "<<findMin(root)<<"\n\n";
    else  cout<<"\n!!! CHILD NOT FOUND !!!\n\n";
    return elementAt( findMin(root));
}

template <class Comperable>
const Comperable & BinarySearchTree<Comperable>::findMax() const
{
    if(findMax(root)!=NULL) cout<<"\nMAX ELEMENT OF TREE IS "<<elementAt(findMax(root))<<"\n\nMEMORY OF CHILD IS "<<findMax(root)<<"\n\n";
    else cout<<"\n!!! CHILD NOT FOUND !!!\n\n";
    return elementAt( findMax(root));
}

template <class Comperable>
BinaryNode<Comperable> * BinarySearchTree<Comperable>::find( const Comperable & x, BinaryNode<Comperable> *t ) const
{
    if( t==NULL)
        return NULL;
    else if(x < t->element)
        return find(x,t->left );
    else if( t->element < x )
        return find(x,t->right );
    else
        
        return t;
}

template <class Comperable>
BinaryNode<Comperable> * BinarySearchTree<Comperable>::findMin( BinaryNode<Comperable> *t) const
{
    if( t==NULL)
        return NULL;
    if( t->left == NULL)
        return t;
    return findMin( t->left );
}

template <class Comperable>
BinaryNode<Comperable> * BinarySearchTree<Comperable>::findMax( BinaryNode<Comperable> *t ) const
{
    if( t != NULL)
        while(t->right !=NULL )
            t = t->right;
    return t;
}

template<class Comperable>
void BinarySearchTree<Comperable>::insert( const Comperable & x )
{
    insert(x,root);
}


template<class Comperable>
void BinarySearchTree<Comperable>::insert( const Comperable & x, BinaryNode<Comperable> * & t ) const
{
    if( t == NULL)
        t = new BinaryNode<Comperable>( x, NULL, NULL);
    else if( x < t->element)
        insert( x, t->left);
    else if( t->element < x )
        insert( x, t->right );
    else
        ;
}

template<class Comperable>
void BinarySearchTree<Comperable>::remove( const Comperable & x)
{
    remove(x,root);
}

template<class Comperable>
void BinarySearchTree<Comperable>::remove( const Comperable & x,BinaryNode<Comperable> * & t) const
{
    if( t == NULL)
        return;
    if( x < t->element)
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL )
    {
        t->element = findMin( t->right )->element;
        remove( x,t->right);
    }
    else
    {
        BinaryNode<Comperable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

template<class Comperable>
BinarySearchTree<Comperable>::~BinarySearchTree()
{
    makeEmpty();
}

template <class Comperable>
void BinarySearchTree<Comperable>::makeEmpty()
{
    makeEmpty(root);
}

template <class Comperable>
void BinarySearchTree<Comperable>::makeEmpty( BinaryNode<Comperable> * & t) const
{
    if( t != NULL )
    {
        makeEmpty( t->left);
        makeEmpty( t->right);
        delete t;
    }
    t = NULL;
}

template <class Comperable>
void BinarySearchTree<Comperable>::printTree(char c) const
{
    if( isEmpty())
        cout<<"Empty Tree";
    else
        switch(c){
            case '1' :
                printTreePre( root );
                break;
            case '2' :
                printTreeIn( root );
                break;
            case '3' :
                printTreePost( root );
                break;
        }
    
}
template <class Comperable>
void BinarySearchTree<Comperable>::printTreePre( BinaryNode<Comperable> *t ) const
{
    if( t != NULL )
    {
        cout<< t->element <<" ";
        printTreePre( t->left );
        printTreePre( t->right);
    }
}

template <class Comperable>
void BinarySearchTree<Comperable>::printTreeIn( BinaryNode<Comperable> *t ) const
{
    if( t != NULL )
    {
        
        printTreeIn( t->left );
        cout<< t->element << " ";
        printTreeIn( t->right);
    }
}

template <class Comperable>
void BinarySearchTree<Comperable>::printTreePost( BinaryNode<Comperable> *t ) const
{
    if( t != NULL )
    {
        
        printTreePost( t->left );
        printTreePost( t->right);
        cout<< t->element << " ";
    }
}

template <class Comperable>
const BinarySearchTree<Comperable> & BinarySearchTree<Comperable>::operator=( const BinarySearchTree<Comperable> & rhs)
{
    if( this != &rhs )
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

template<class Comperable>
BinaryNode<Comperable> * BinarySearchTree<Comperable>::clone(BinaryNode<Comperable> * t ) const
{
    if(t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable>( t->element, clone(t->left),clone(t->right));
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const
{
    return root == NULL;
}


#endif /* bst_h */
