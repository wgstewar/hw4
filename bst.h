#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
		int calculateHeightIfBalanced(Node<Key, Value>* root, bool* unbalancedbool) const;
		void promote(Node<Key, Value>* toPromote);
		void postOrderTraveralClear(Node<Key, Value>* curr);
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
		this->current_ = ptr;

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
		this->current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		return(this->current_ == (&rhs)->current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		return(this->current_ != (&rhs)->current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		this->current_ = successor(this->current_);
		return *this; 

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
		this->root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		this->clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
/*
  Youre writing while loop - go until you find empty 
  spot to insert node OR find a key that’s exact same val, 
  then update key’s value - shouldn’t be doing more than 
  log(n) runs 
*/

template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
  // TODO
	if (this->root_ == NULL)
	{
		//std::cout << "entered and key is " << (&keyValuePair)->first << std::endl;
		Node<Key, Value>* insertroot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		this->root_ = insertroot;
		return;
	}
  Node<Key, Value>* current = this->root_;
	Node<Key, Value>* currentcopy = this->root_;
	bool insertedAlready = 0;
	
  while (current != NULL)
  {
      if (current->getKey() > keyValuePair.first)
      {
					currentcopy = current;
					current = current->getLeft();
      }
      else if (current->getKey() < keyValuePair.first)
      {
					currentcopy = current;
          current = current->getRight();
      }
      else // (current->getKey == (&KeyValuePair)->getKey)
      {
          current->setValue(keyValuePair.second);
					insertedAlready = 1;
					break;
      }
  }
	if (!insertedAlready) // create a new leaf node with currentcopy as the parent 
	{
		Node<Key, Value>* insertleaf = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, currentcopy);
		if (insertleaf->getKey() > currentcopy->getKey()) // insert right leaf
		{
			currentcopy->setRight(insertleaf);
		}
		else // insert left leaf
		{
			currentcopy->setLeft(insertleaf);
		}
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
		Node<Key, Value>* nodeToRemove = internalFind(key);
		if (nodeToRemove == NULL) // node not in tree 
		{
			return;
		}
        // 2 children
		if (nodeToRemove->getLeft() != NULL && nodeToRemove->getRight() != NULL)
		{
            
			Node<Key, Value>* predec = predecessor(nodeToRemove); 
			nodeSwap(nodeToRemove, predec); // this will make predecessor the root if nodeToRemove was the root
		}
		// no children
		if (nodeToRemove->getLeft() == NULL && nodeToRemove->getRight() == NULL)
		{
			if (nodeToRemove == this->root_) // no children, and it's the root - must be the only node in tree 
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
			promote(nodeToRemove->getLeft());
			delete nodeToRemove;
			nodeToRemove = NULL;
		}
		// 1 child (right)
		else if (nodeToRemove->getLeft() == NULL && nodeToRemove->getRight() != NULL)
		{
			promote(nodeToRemove->getRight());
			delete nodeToRemove;
			nodeToRemove = NULL;
		}
}
 
 
 //4 is on the right of the node were removing BUT its on the left of the grandparent node 


// promote
// set grandparent of node toPromote to be the parent of toPromote
// set the child of the old grandparent of toPromote to be toPromote instead of toPromote's parent 
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::promote(Node<Key, Value>* toPromote)
{
	if (toPromote->getParent() == this->root_) // is nodeToRemove is the root node, need to make nodetoPromote the new root_
	{
		this->root_ = toPromote;
	}
	Node<Key, Value>* grandparent = (toPromote->getParent())->getParent(); 
	if (grandparent != NULL) // if we didnt just make it a root_
	{
		if (toPromote->getParent() == grandparent->getLeft())
		{
			grandparent->setLeft(toPromote); 
		}
		else if (toPromote->getParent() == grandparent->getRight())
		{
			grandparent->setRight(toPromote);
		}
	}
	toPromote->setParent(grandparent);
	//else
	//{
	//	toPromote->setParent(NULL);
	//}
}




template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
		if (current == NULL)
		{
			return NULL;
		}
		Node<Key, Value>* currentcopy;
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
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
		if (current == NULL)
		{
			return NULL;
		}
		Node<Key, Value>* currentcopy;
		if (current->getRight() != NULL)
		{
			current = current->getRight();
			currentcopy = current;
			while (current != NULL)
			{
				current = current->getLeft();
				if (current != NULL)
				{
					currentcopy = current;
				}
			}
			return currentcopy;
		}
		else // no right child
		{
			if (current->getParent() == NULL) // we've reached root since parent of current = null 
			{
				return NULL;
			}
			while(current != (current->getParent())->getLeft())
			{
				current = current->getParent();
				if (current->getParent() == NULL) // we've reached root since parent of current = null 
				{
					return NULL;
				}
			}
			return current->getParent();
		}
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
		postOrderTraveralClear(this->root_);
		this->root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::postOrderTraveralClear(Node<Key, Value>* curr)
{
	if (curr == NULL)
	{
		return;
	}

	postOrderTraveralClear(curr->getLeft());
	postOrderTraveralClear(curr->getRight());
	
	//remove(curr->getKey());
	delete curr;
	curr = NULL; 
}



/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
		Node<Key, Value>* current = this->root_;
		while(current != NULL)
		{
			if (current->getLeft() == NULL)
			{
				return current;
			}
			current = current->getLeft();
		}
		return NULL; // root was NULL
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
	if (this->root_ == NULL)
	{
		return NULL;
	}
	Node<Key, Value>* current = this->root_;
	if (current->getKey() == key)
	{
		return current;
	}
	//bool foundAlready = 0;
  while(current != NULL)
  {
      if(current->getKey() > key)
      {
          current = current->getLeft();
      }
      else if(current->getKey() < key)
      {
          current = current->getRight();
      }
      else // (current->getKey == key)
      {
          return current;
      }
  }
	return current; // current = NULL at this point (key not found) 
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
  if (this->root_ == NULL)
	{
		return true;
	}
	bool unbalancedbl = false;
	this->calculateHeightIfBalanced(this->root_, &unbalancedbl);
	if (unbalancedbl)
	{
		return false;
	}
	else 
	{
		return true;
	}
}

/// @brief Calculates the height of the tree if it is balanced. Otherwise returns -1.
/// @param root The root of the tree to calculate height of
/// @return the height of the tree if its balanced, otherwise -1
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(Node<Key, Value>* root, bool* unbalancedbool) const
{
	// Base case: an empty tree is always balanced and has a height of 0
	if (root == NULL) return 0;

	// Think about cases to handle:
	// - What if at least one subtree is NOT balanced?
	// - What if BOTH are balanced?
	int leftheight = this->calculateHeightIfBalanced(root->getLeft(), unbalancedbool) + 1; // getleft needs creating
	int rightheight = this->calculateHeightIfBalanced(root->getRight(), unbalancedbool) + 1; // create getright
	if ((leftheight-rightheight > 1) || (leftheight-rightheight < -1)) // if the tree is inbalanced from this root's perspective  
	{
		*unbalancedbool = true; 
		//return -1;
		//return balancedbool;
	}
	return std::max(leftheight, rightheight); // return height of tree 
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
