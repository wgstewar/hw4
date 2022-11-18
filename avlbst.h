#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child);
void removeFix(AVLNode<Key, Value>* n, int8_t diff);
void rotateLeft(AVLNode<Key, Value>* axis);
void rotateRight(AVLNode<Key, Value>* axis);
static AVLNode<Key, Value>* avlpredecessor(AVLNode<Key, Value>* current);
};

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::avlpredecessor(AVLNode<Key, Value>* current)
{
    // TODO
		if (current == NULL)
		{
			return NULL;
		}
		AVLNode<Key, Value>* currentcopy;
		if (current->getLeft() != NULL)
		{
			current = current->getLeft();
			currentcopy = current;
			while (current != NULL)
			{
				current = current->getRight();
				if (current != NULL)
				{
					currentcopy = current;
				}
			}
			return currentcopy;
		}
		else // no left child
		{
			if (current->getParent() == NULL) // we've reached root since parent of current = null 
			{
				return NULL;
			}
			while(current != (current->getParent())->getRight())
			{
				current = current->getParent();
				if (current->getParent() == NULL)
				{
					return NULL;
				}
			}
			return current->getParent();
		}
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* axis)
{
	AVLNode<Key, Value>* child = axis->getLeft();
	AVLNode<Key, Value>* gparent = axis->getParent();
	if (child != NULL)
	{
		child->setParent(gparent);
	}
	if (gparent != NULL)
	{
		if (gparent->getLeft() == axis)
		{
			gparent->setLeft(child);
		}
		else 
		{
			gparent->setRight(child);
		}
	}
	else
	{
		this->root_ = static_cast<Node<Key, Value>*>(child);
	}
	if (child != NULL) 
	{
		axis->setLeft(child->getRight());
		if (child->getRight() != NULL)
		{
			child->getRight()->setParent(axis);
		}
		child->setRight(axis); 
	}
	axis->setParent(child);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* axis)
{
	AVLNode<Key, Value>* child = axis->getRight();
	AVLNode<Key, Value>* gparent = axis->getParent();

	if (child!= NULL)
	{
		child->setParent(gparent);
	}
	if (gparent != NULL)
	{
		child->setParent(gparent);
		if (gparent->getLeft() == axis)
		{
			gparent->setLeft(child);
		}
		else 
		{
			gparent->setRight(child);
		}
	}
	else 
	{
		this->root_ = static_cast<Node<Key, Value>*>(child);
	}
	axis->setRight(child->getLeft());
	if (child->getLeft() != NULL)
	{
		child->getLeft()->setParent(axis);
	}
	child->setLeft(axis); 
	axis->setParent(child);
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if (static_cast<AVLNode<Key, Value>*>(this->root_) == NULL)
	{
		AVLNode<Key, Value>* insertroot = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
		this->root_ = static_cast<Node<Key, Value>*>(insertroot);
		return;
	}
  AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
  AVLNode<Key, Value>* currentcopy = static_cast<AVLNode<Key, Value>*>(this->root_);
  bool insertedAlready = 0;

  while (current != NULL)
  {
      if (current->getKey() > new_item.first)
      {
					currentcopy = current;
					current = current->getLeft();
      }
      else if (current->getKey() < new_item.first)
      {
					currentcopy = current;
          current = current->getRight();
      }
      else // (current->getKey == (&new_item)->getKey)
      {
          current->setValue(new_item.second);
					insertedAlready = 1;
					break;
      }
  }
	if (!insertedAlready) // create a new leaf node with currentcopy as the parent 
	{
		AVLNode<Key, Value>* insertleaf = new AVLNode<Key, Value>(new_item.first, new_item.second, currentcopy);
		if (insertleaf->getKey() > currentcopy->getKey()) // insert right leaf
		{
			currentcopy->setRight(insertleaf);
			if (currentcopy->getBalance() == 0) // parent had no children 
			{
				currentcopy->updateBalance(1);
				insertFix(currentcopy, currentcopy->getRight()); // sending parent and node to insertFix
			}
			else if (currentcopy->getBalance() == -1) // parent already has a left child
			{
				currentcopy->updateBalance(1); // setting parent balance to 0 since it now has a child on each side 
			}
		}
		else // insert left leaf
		{
			currentcopy->setLeft(insertleaf);
			if (currentcopy->getBalance() == 0) // parent has no children 
			{
				currentcopy->updateBalance(-1);
				insertFix(currentcopy, currentcopy->getLeft()); // sending parent and node to insertFix
			}
			else if (currentcopy->getBalance() == 1) // parent already has a right child
			{
				currentcopy->updateBalance(-1);
			}	
		}
	}
}
//after you balance the granparent with rotating you have to 
// see if you affected balance up higher 

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child)
{
	if (parent == NULL)
	{
		return;
	}
	AVLNode<Key, Value>* gparent = parent->getParent();
	if (gparent == NULL)
	{
		return; 
	}
	bool zigzig = 0;
	bool zigzag = 0;
	if (gparent->getLeft() == parent) // parent is a left child of gparent
	{
		gparent->updateBalance(-1);
		//if (parent->getRight() == NULL) // child is left of parent
		if (parent->getBalance() == -1) // parent is left heavy by 1 after insertion
		{
			zigzig = true;
		}
		else if (parent->getBalance() == 1) // parent is left heavy by 1 after insertion
		{
			zigzag = true;
		}
	}
	else if (gparent->getRight() == parent) // parent is a right child of gparent 
	{
		gparent->updateBalance(1);
		//if (parent->getLeft() == NULL)
		if (parent->getBalance() == 1)
		{
			zigzig = true;
		}
		else if (parent->getBalance() == -1) 
		{
			zigzag = true;
		}
	}	
	// after update gparent's balance: 
	if (gparent->getBalance() == 0) // was -1 and right height incremented, or was 1 and left height incremented 
	{
		return;
	}
	else if (gparent->getBalance() == -1 || gparent->getBalance() == 1) // gparent's parent might be unbalanced now 
	{
		insertFix(gparent, parent);
	}
	else if (gparent->getBalance() == -2) // fix the balance here 
	{
		if (zigzig)
		{
			rotateRight(gparent);
			gparent->setBalance(0);
			parent->setBalance(0);
			return;
		} 
		else if (zigzag)
		{
			rotateLeft(parent);
			rotateRight(gparent);
			if (child->getBalance() == -1)
			{
				parent->setBalance(0);
				gparent->setBalance(1);
				child->setBalance(0);
			}
			else if (child->getBalance() == 0)
			{
				parent->setBalance(0);
				gparent->setBalance(0);
				child->setBalance(0);
			}
			else if (child->getBalance() == 1)
			{
				parent->setBalance(-1);
				gparent->setBalance(0);
				child->setBalance(0);
			}
		}
	}	
	else if (gparent->getBalance() == 2) // fix the balance here
	{
		if (zigzig)
		{
			rotateLeft(gparent);
			gparent->setBalance(0);
			parent->setBalance(0);
			return;
		} 
		else if (zigzag)
		{
			rotateRight(parent);
			rotateLeft(gparent);
			if (child->getBalance() == 1)
			{
				parent->setBalance(0);
				gparent->setBalance(-1);
				child->setBalance(0);
			}
			else if (child->getBalance() == 0)
			{
				parent->setBalance(0);
				gparent->setBalance(0);
				child->setBalance(0);
			}
			else if (child->getBalance() == -1)
			{
				parent->setBalance(1);
				gparent->setBalance(0);
				child->setBalance(0);
			}
		}
	}
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
		AVLNode<Key, Value>* nodeToRemove = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
		if (nodeToRemove == NULL) // node not in tree 
		{
			return;
		}
    // 2 children
		if (nodeToRemove->getLeft() != NULL && nodeToRemove->getRight() != NULL)
		{    
			//Node<Key, Value>* bstpredec = BinarySearchTree<Key, Value>::predecessor(nodeToRemove); 
			//AVLNode<Key, Value>* predec = bstpredec 
			AVLNode<Key, Value>* predec = avlpredecessor(nodeToRemove); 
			nodeSwap(nodeToRemove, predec); // this will make predecessor the root if nodeToRemove was the root
		}
		// NEW
		AVLNode<Key, Value>* p = nodeToRemove->getParent();
		int8_t diff = 0; 
		if (p != NULL)
		{
			if (p->getLeft() == nodeToRemove) // node to remove was a left child
			{
				diff = 1;
			}
			if (p->getRight() == nodeToRemove) // node to remove was a right child
			{
				diff = -1;
			}
		}
		//NEW END 
		// no children
		if (nodeToRemove->getLeft() == NULL && nodeToRemove->getRight() == NULL)
		{
			if (nodeToRemove == static_cast<AVLNode<Key, Value>*>(this->root_)) // no children, and it's the root - must be the only node in tree 
			{
			    this->clear();
					return;
			}
			else if (nodeToRemove->getParent()->getLeft() == nodeToRemove)
			{
				(nodeToRemove->getParent())->setLeft(NULL);	
			}
			else if (nodeToRemove->getParent()->getRight() == nodeToRemove)
			{
				(nodeToRemove->getParent())->setRight(NULL);	
			}
			delete nodeToRemove;
			nodeToRemove = NULL; 
		}
		// 1 child (left)
		else if (nodeToRemove->getLeft() != NULL && nodeToRemove->getRight() == NULL)
		{
			BinarySearchTree<Key, Value>::promote(nodeToRemove->getLeft());
			delete nodeToRemove;
			nodeToRemove = NULL;
		}
		// 1 child (right)
		else if (nodeToRemove->getLeft() == NULL && nodeToRemove->getRight() != NULL)
		{
			BinarySearchTree<Key, Value>::promote(nodeToRemove->getRight());
			delete nodeToRemove;
			nodeToRemove = NULL;
		}
		//NEW 
		removeFix(p, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int8_t diff)
{
	if (n == NULL) // v is the root 
	{
		return;
	}
	AVLNode<Key, Value>* p = n->getParent();
	int8_t ndiff = 0;
	if (p != NULL)
	{
		if (p->getLeft() == n) // n is a left child
		{
			ndiff = 1;
		}
		else if (p->getRight() == n) // n is a right child 
		{
			ndiff = -1;
		}
	}
	// if diff == -1
	if (diff == -1) // removed from right side
	{
		if (n->getBalance() + diff == -2) // n's balance is already -1
		{
			AVLNode<Key, Value>* c = n->getLeft(); 
			// now check whether it's zigzig or zigzag, on the left side of p
			if (c->getBalance() == -1) // zigzig
			{
				rotateRight(n); 
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, ndiff);
			}
			else if (c->getBalance() == 0) // zigzig
			{
				rotateRight(n); 
				n->setBalance(-1);
				c->setBalance(1);
			}
			else if (c->getBalance() == 1) // zigzag
			{
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(c);
				rotateRight(n);
				if (g->getBalance() == 1)
				{
					n->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0);
					
				}
				else if (g->getBalance() == 0)
				{
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if (g->getBalance() == -1)
				{
					n->setBalance(1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, ndiff);
			}
		}
		else if (n->getBalance() + diff == -1)
		{
			n->setBalance(-1);
		}
		else if (n->getBalance() + diff == 0)
		{
			n->setBalance(0);
			removeFix(p, ndiff);
		}
	}
	// if diff == 1
	else if (diff == 1) // removed from left side
	{
		if (n->getBalance() + diff == 2) // n's balance was already 1
		{
			AVLNode<Key, Value>* c = n->getRight();
			if (c->getBalance() == 1) // zigzig
			{
				rotateLeft(n); 
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, ndiff);
			}
			else if (c->getBalance() == 0) // zigzig
			{
				rotateLeft(n); 
				n->setBalance(1);
				c->setBalance(-1);
			}
			else if (c->getBalance() == -1) // zigzag
			{
				AVLNode<Key, Value>* g = c->getLeft();
				rotateRight(c);
				rotateLeft(n);
				if (g->getBalance() == -1)
				{
					n->setBalance(0);
					c->setBalance(1);
					g->setBalance(0);
					
				}
				else if (g->getBalance() == 0)
				{
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if (g->getBalance() == 1)
				{
					n->setBalance(-1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, ndiff);
			}
		}
		else if (n->getBalance() + diff == 1) // n's balance was 0
		{
			n->setBalance(1);
		}
		else if (n->getBalance() + diff == 0) // n's balance was -1
		{
			n->setBalance(0);
			removeFix(p, ndiff);
		}

	}


}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
