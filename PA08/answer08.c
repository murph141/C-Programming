#include "pa08.h"
#include <stdio.h>
#include <stdlib.h>

void SparseArray_merge_helper(SparseNode *, SparseNode *);


/* 
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This Sparse array will be implemented by a binary tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates
 * memory for a sparse array tree node, and it copies the integer values, and sets the 
 * subtree pointers to NULL. 
 */

SparseNode *SparseNode_create(int index, int value)
{
  SparseNode * ln = malloc(sizeof(SparseNode)); //Allocate memory

  // Check for memory allocation errors
  if(ln == NULL)
  {
    printf("Memory Allocated Incorrectly (SparseNode_create).\n");
    return NULL;
  }

  //Set values
  ln -> right = NULL;
  ln -> left = NULL;
  ln -> value = value;
  ln -> index = index;

  return ln;
}

/* Add a particular value into a sparse array tree on a particular index.
 *
 * Arguments:
 * *array        the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse 
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */

SparseNode * SparseArray_insert( SparseNode * array, int index, int value )
{
  // If nothing exists
  if (array == NULL)
  {
    if(value)
    {
      return SparseNode_create(index, value);
    }
    else
    {
      return NULL;
    }
  }

  // The index already exists
  if((array -> index) == index)
  {
    if(value)
    {
      (array -> value) = value;
    }
    return array;
  }

  if((array -> index) > index)
  {
    (array -> left) = SparseArray_insert((array -> left), index, value);
    return array;
  }

  array -> right = SparseArray_insert((array -> right), index, value);
  return array;
}

/* Build a sparse array tree from given indices and values with specific length.
 *
 * Arguments:
 * index*         a pointer points to the start position of the index array
 * value*         a pointer points to the start position of the value array
 * length         the size of both array
 * 
 * returns:
 * SparseNode *   the pointer points to the root node of sparse array tree
 *                just constructed
 *
 * It returns a sparse array tree. 
 * You need to insert tree nodes in order
 *
 * (the first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1]. Basically, each tree node is constructed
 * with each pair in indices and values array. In other words, elements of 
 * indices and values with the same index should go into the same node.)
 */

SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  int i;
  SparseNode * root = NULL;

  // Iterate through all of the indicies and values
  for(i = 0; i < length; i++)
  {
    root = SparseArray_insert(root, indicies[i], values[i]);
  }

  return root;
}

/* Destroy an entire sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * void
 *
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseArray_destroy ( SparseNode * array )
{
  if(array == NULL)
  {
    return;
  }

  // Go all the way to the end then start freeing afterwards
  SparseArray_destroy(array -> left);
  SparseArray_destroy(array -> right);

  free(array);
}

/* Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the smallest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMin ( SparseNode * array )
{
  // Go all the way to the left then return the index
  while(array -> left != NULL)
  {
    array = array -> left;
  }

  return (array -> index);
}

/* Retrieve the largest index in the sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the largest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMax ( SparseNode * array )
{
  // Go all the way to the right then return the index
  while(array -> right != NULL)
  {
    array = array -> right;
  }

  return (array -> index);
}


/* Retrieve the node associated with a specific index in a sparse
 * array tree.  
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to search
 * 
 * returns:
 * SparseNode*    the node with the index that you searched from the tree.
 *                If no node found, NULL should be returned. 
 *                
 * Hint: If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int ind)
{
  // If array is empty, return NULL
  if(array == NULL)
  {
    return NULL;
  }

  // Found the index
  if((array -> index) == ind)
  {
    return array;
  }

  if((array -> index) > ind)
  {
    return SparseArray_getNode(array -> left, ind);
  }

  return SparseArray_getNode(array -> right, ind);
}

/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array tree ( binary tree root ). 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to remove
 * 
 * returns:
 * SparseNode*    the root node of the sparse array tree that you just modified
 *          
 *    
 * HINT : First, you need to find that node. Then, you will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.

 * - If both subtrees are empty, you can just remove the node.

 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.

 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
 */
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  // If the array is empty, return NULL
  if (array == NULL)
  {
    return NULL;
  }

  // Go to the left of the array 
  if(index < (array -> index))
  {
    array -> left = SparseArray_remove(array -> left, index);
    return array;
  }

  // Go to the right of the array 
  if(index > (array -> index))
  {
    array -> right = SparseArray_remove(array -> right, index);
    return array;
  }

  // Leaf node
  if(((array -> left) == NULL) && ((array -> right) == NULL))
  {
    free(array);
    return NULL;
  }

  // One member to the right
  if((array -> left) == NULL)
  {
    SparseNode * node = array -> right;
    free(array);
    return node;
  }

  // One member to the left
  if((array -> right) == NULL)
  {
    SparseNode * node2 = array -> left;
    free(array);
    return node2;
  }

  // Remember the location of the right member
  SparseNode * newNode = array -> right;

  // Keep going to the left until it is empty
  while((newNode -> left) != NULL)
  {
    newNode = newNode -> left;
  }

  // Copy the index and value in to the new node
  array -> index = newNode -> index;
  array -> value = newNode -> value;
  newNode -> index = index;

  //Go through the function again
  array -> right = SparseArray_remove(array -> right, index);
  return array;
}

/* The function makes a copy of the input sparse array tree
 * and it returns a new copy. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                copied from the input sparse array tree.
 *       
 */

SparseNode * SparseArray_copy(SparseNode * array)
{
  // If array is NULL, return NULL
  if(array == NULL)
  {
    return NULL;
  }

  // Allocate space for a new node
  SparseNode * newNode = malloc(sizeof(SparseNode));

  // Check for memory errors
  if(newNode == NULL)
  {
    printf("Memory Allocated Incorrectly (SparseArray_copy).\n");
    return NULL;
  }

  // Set values
  newNode -> left = NULL;
  newNode -> right = NULL;
  newNode -> index = array -> index;
  newNode -> value = array -> value;

  // Deep copy, parse through rest of the binary tree
  newNode -> right = SparseArray_copy(array -> right);
  newNode -> left = SparseArray_copy(array -> left);

  // Return binary tree
  return newNode;
}

/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * *array_1         the root node of the first sparse array tree
 * *array_2         the root node of the second sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                merged from the two input sparse array tree
 *     
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 * Hint: you may write new functions
 */

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  // Copy the first array into a copy array
  SparseNode * copy = SparseArray_copy(array_1);

  // If array_2 isn't NULL merge it, if it is just return the copy of array_1
  if(array_2 != NULL)
  {
    // Call the merge helper function
    SparseArray_merge_helper(copy, array_2);

    // Check if the binary tree is empty, if it is, set copy equal to NULL
    if(copy -> value == 0)
    {
      copy = NULL;
    }
  }

  // Return binary tree
  return copy;
}

void SparseArray_merge_helper(SparseNode * n1, SparseNode * n2)
{
  if(n2 == NULL)
  {
    return;
  }

  // Go to the end of the binary tree
  SparseArray_merge_helper(n1, n2 -> left);
  SparseArray_merge_helper(n1, n2 -> right);

  // Find the node that contains the index of the leaf node of n2
  SparseNode * node = SparseArray_getNode(n1, n2 -> index);

  // If there is no node with the same index
  if(node == NULL)
  {
    n1 = SparseArray_insert(n1, n2 -> index, n2 -> value);
  }
  // If there is a node with the same index
  else
  {
    // If the values are opposite values, remove the node
    if(((node -> value) + (n2 -> value)) == 0 )
    {
      n1 = SparseArray_remove(n1, node -> index);
    }
    else
    // If the values are different values that aren't oppositves, add them up and set the value equal to their sum
    {
      n1 = SparseArray_insert(n1, n2 -> index, (n2 -> value) + (node -> value));
    }
  }
}
