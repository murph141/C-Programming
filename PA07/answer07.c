#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
  while(head != NULL)
  {
    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
    head = head -> next;
  }
  printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  if(head == NULL)
  {
    return; //When head doesn't point to anything, return and start freeing
  }
  List_destroy(head -> next);
  free(head);
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  Node * ln = malloc(sizeof(Node));

  //Check for incorrectly allocated memory
  if(ln == NULL)
  {
    printf("Memory Allocated Incorrectly (List_create Function).\n");
    return NULL;
  }

  ln -> next = NULL;
  ln -> value = value;
  ln -> index = index;

  return ln;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
  int i = 0; //Counter variable
  Node * head = NULL; //Initialize the variable to NULL

  while(i != length)
  {
    head = List_insert_ascend(head, value[i], index[i]);
    i++; //Increment i
  }

  return head;
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  if(head == NULL)
  {
    head = List_create(value, index); // Create a new list if the node is NULL
  }
  else
  {
    if(index == head -> index)
    {
      head -> value += value; //Add values together if indicies are the same
    }

    if(index > head -> index)
    {
      head -> next = List_insert_ascend(head -> next, value, index); //Call the function again if the index is too big
    }

    if(index < head -> index)
    {
      Node * p = head; //Point to next value
      head = List_create(value, index); //Add a value to the node
      head -> next = p; //Have the last node point to the previous last node
    }
  }

  return head;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
  if(head == NULL)
  {
    return NULL; //If the node is NULL just return NULL
  }
  if((head -> index) == index)
  {
    Node * p = head -> next; //Remember the address of the next value
    free(head); //Release memory
    return p;
  }
  head -> next = List_delete(head -> next, index); //Recall the delete function if index is not found
  return head;
}

Node * List_getNode(Node * head, int index)
{
  if(head == NULL)
  {
    return NULL; //If the node is NULL, there is nothing to get
  }

  if ((head -> index) == index)
  {
    return head; //Return the address if foun
  }
  return List_getNode(head -> next, index); //Recall the function
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head)
{
  if(head == NULL)
  {
    return NULL; //Return NULL if head is NULL
  }

  Node * newNode = malloc(sizeof(Node)); //Allocate space

  //Check that memory was allocated correctly
  if(newNode == NULL)
  {
    printf("Memory Allocated Incorrectly (List_delete Function).\n");
    return NULL;
  }

  //Copy the values
  newNode -> next = NULL;
  newNode -> value = head -> value;
  newNode -> index = head -> index;

  //Recall function to get a "deep" copy
  newNode -> next = List_copy(head -> next);

  return newNode;
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */

Node * List_merge(Node * head1, Node * head2)
{
  Node * copy = List_copy(head1);

  //Go through the head2 structure
  while(head2 != NULL)
  {
    //Copy is equal to itself plus the value and index of head2
    copy = List_insert_ascend(copy, head2 -> value, head2 -> index);

    //If the node's values at head2's index is 0, delete the node
    if(List_getNode(copy, head2 -> index) -> value == 0)
    {
      copy = List_delete(copy, head2 -> index); //Delete the node
    }

    head2 = head2 -> next; //Move through the head2 structure
  }

  return copy;
}
