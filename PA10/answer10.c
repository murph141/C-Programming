#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

//Function declarations
int locate(int *, int, int);
void destroy_helper(ListNode *);
int findmax(int *, int);
int findmin(int *, int);
void permute(int *, int, int);
void swap(int *, int*);

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * stack = malloc(sizeof(Stack)); //Allocate space
  stack -> list = NULL; //Make the pointer to the next list NULL

  return stack;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  if(stack == NULL)
  {
    return; //Return if stack is NULL
  }

  destroy_helper(stack -> list); //Call the helper function to take care of the linked list
  free(stack); //Free the stack
}

void destroy_helper(ListNode * list)
{
  if(list == NULL)
  {
    return;
  }

  destroy_helper(list -> next); //Call the function again with the next list
  free(list); //Free the current list
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if(stack -> list == NULL) //If the stack is empty, return true
  {
    return TRUE;
  }

  return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
  if(stack == NULL) //If stack is NULL, return a negative number
  {
    return -1;
  }

  int value = stack -> list -> value; //Set the value to the first linked list item's value

  ListNode * list = stack -> list; //Make a linked list pointer to the first item of the stack
  stack -> list = list -> next; //Have the stack point to the second item in the linked list
  free(list); //Free the first item in the linked list

  return value; //Return the value that was popped off of the stack
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */

void Stack_push(Stack * stack, int value)
{
  ListNode * list = malloc(sizeof(ListNode)); //Allocate space for a linked list item

  list -> value = value; //Set the list value to the given value
  list -> next = stack -> list; //Set the next list item to the first stack item

  stack -> list = list; //Set the first linked list item to the linked list pointer
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{
  if(!isStackSortable(array, len)) //Don't do anything if you are unable to sort the stack
  {
    return;
  }

  int write_index = 0; //the write index
  int ind = 0; //the index of the array
  int value = 0; //the value that will store the value that will be popped off the stack

  Stack * st = Stack_create(); //Create a new stack

  for(; ind < len; ind++)
  {
    while(st -> list != NULL && (st -> list -> value < array[ind]))
    {
      value = Stack_pop(st);
      array[write_index] = value; //Put the popped value into an array
      write_index++; //Increment the write index
    }
    Stack_push(st, array[ind]); //Push the item on to the stack
  }
  while(st -> list != NULL)
  {
    value = Stack_pop(st);
    array[write_index] = value; //Put the popped value into an array
    write_index++; //Increment the write index
  }

  Stack_destroy(st); //Destroy the stack
}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int isStackSortable(int * array, int len)
{
  if(len < 3) //If length is less than 3, the stack is automatically sortable
  {
    return TRUE;
  }

  int max = findmax(array, len); //Find the max value
  int loc = locate(array, max, len); //Find the location of the max value

  if(loc == len - 1) //If you are at the end of the array, just call the function again with the first part
  {
    return isStackSortable(array, loc);
  }
  else if(loc == 0) //If you are at the beginning of the array, just call the function again with the second part
  {
    return isStackSortable(array + 1, len - 1);
  }
  else
  {
    if(findmax(array, loc) >= findmin(&array[loc + 1], len - loc - 1))
    {
      return FALSE;
    }
  }

  return (isStackSortable(array, loc) * isStackSortable(&array[loc + 1], len - loc - 1)); //Return the first half and the second half outcomes multiplied by each other
}

int locate(int * array, int val, int len)
{
  int i = 0; //Temp value
  int loc = 0; //Location value

  for(; i < len; i++)
  {
    if(array[i] != val)
    {
      loc++; //Increment the location value
    }
    else
    {
      i = len; //If value is found, exit the loop
    }
  }

  return loc; //Return the location
}


int findmax(int * array, int len)
{
  int ind; //Index value
  int max; //Max value

  for(ind = 0; ind < len; ind++)
  {
    if(!ind)
    {
      max = array[ind]; //Max is equal to the first item scanned in
    }
    else
    {
      if(max < array[ind])
      {
        max = array[ind]; //Max is equal to the new higher value
      }
    }
  }

  return max;
}


int findmin(int * array, int len)
{
  int ind; //Index value
  int min; //Min value

  for(ind = 0; ind < len; ind++)
  {
    if(!ind)
    {
      min = array[ind]; //Min is equal to the first item scanned in
    }
    else
    {
      if(min > array[ind])
      {
        min = array[ind]; //Min is equal to the new lower value
      }
    }
  }

  return min;
}


/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
void genShapes(int k)
{
  int arr[k]; //Create the array with k values
  int index; //Hold the index values

  for(index = 0; index < k; index++)
  {
    arr[index] = index; //Populate the array with values 0 through k-1
  }

  permute(arr, k, 0); //Call the permute function
}

void permute(int * array, int k, int index)
{
  if (index == k) //Call if the values are equal
  {
    if(isStackSortable(array, k)) //Check for sortability
    {
      TreeNode * tr = Tree_build(array, k); //Create a binary tree
      Tree_printShape(tr); //Print the binary tree
      Tree_destroy(tr); //Destroy the binary tree
    }
  }

  int ind = index; //Set ind to the index value
  for(; ind < k; ind++)
  {
    swap(&array[ind], &array[index]); //Swap values
    permute(array, k, index + 1); //Call the permute function with the swapped valuse
    swap(&array[ind], &array[index]); //Swap the values back
  }
}

void swap(int * array, int * array2)
{
  int t = *array; //Save the first value
  *array = *array2; //Set the first value to the second value
  *array2 = t; //Set the second value to the saved first value
}
