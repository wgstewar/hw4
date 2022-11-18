#include "equal-paths.h"
#include <algorithm>
using namespace std;


// You may add any prototypes of helper functions here
int equalPathsHelper(Node * root);

bool equalPaths(Node * root)
{
    // Add your code below

  if (root == nullptr)
  {
    return true;
  }
  else if (root->left == nullptr && root->right == nullptr)
  {
            return 1; // no right or left node
  }
  else if (equalPathsHelper(root) == -1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

int equalPathsHelper(Node * root)
{
    int lHeight = 0;
    int rHeight = 0;
  
  if (root->left == nullptr) 
  {
    if (root->right == nullptr) // leaf node
    {
      return 0;
    }
    else // there's a right child but no left 
    {
      rHeight = equalPathsHelper(root->right);
      /*if (lHeight == 0)
      {
        return -1
      }*/
    }
  }
  else if (root->right == nullptr) // left child but no right child
  {
        lHeight = equalPathsHelper(root->left);
        /*if (lHeight == 0)
        {
          return -1
        }*/
  }
  else // there's a right and left subtree 
  {
    // check if left and right subtree are each equal 
    // and if left subtree height = right subtree height 
    lHeight = equalPathsHelper(root->left); 
    rHeight = equalPathsHelper(root->right);
    //return std::max(rHeight, lHeight); // returns larger height 
  }
  if (lHeight == rHeight)
  {
    return lHeight + 1; 
  }     
  else 
  {
    return -1; 
  }
  
}
