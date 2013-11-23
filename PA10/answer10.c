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
  Stack * stack = malloc(sizeof(Stack));
  stack -> list = NULL;

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
    return;
  }

  destroy_helper(stack -> list);
  free(stack);
}

void destroy_helper(ListNode * list)
{
  if(list == NULL)
  {
    return;
  }

  destroy_helper(list -> next);
  free(list);
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if(stack -> list == NULL)
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
  if(stack == NULL)
  {
    return -1;
  }

  int value = stack -> list -> value;

  ListNode * list = stack -> list;
  stack -> list = list -> next;
  free(list);

  return value;
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
  ListNode * list = malloc(sizeof(ListNode));

  list -> value = value;
  list -> next = stack -> list;

  stack -> list = list;
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
  if(!isStackSortable(array, len))
  {
    return;
  }

  int write_index = 0;
  int ind = 0;
  int value = 0;

  Stack * st = Stack_create();

  for(; ind < len; ind++)
  {
    while(st -> list != NULL && (st -> list -> value < array[ind]))
    {
      value = Stack_pop(st);
      array[write_index] = value;
      write_index++;
    }
    Stack_push(st, array[ind]);
  }
  while(st -> list != NULL)
  {
    value = Stack_pop(st);
    array[write_index] = value;
    write_index++;
  }

  Stack_destroy(st);
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
  if(len < 3)
  {
    return TRUE;
  }

  int max = findmax(array, len);
  int loc = locate(array, max, len);

  if(loc == len - 1)
  {
    return isStackSortable(array, loc);
  }
  else if(loc == 0)
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

  return (isStackSortable(array, loc) * isStackSortable(&array[loc + 1], len - loc - 1));
}

int locate(int * array, int val, int len)
{
  int i = 0;
  int loc = 0;

  for(; i < len; i++)
  {
    if(array[i] != val)
    {
      loc++;
    }
    else
    {
      i = len;
    }
  }

  return loc;
}


int findmax(int * array, int len)
{
  int ind;
  int max;

  for(ind = 0; ind < len; ind++)
  {
    if(!ind)
    {
      max = array[ind];
    }
    else
    {
      if(max < array[ind])
      {
        max = array[ind];
      }
    }
  }

  return max;
}


int findmin(int * array, int len)
{
  int ind;
  int min;

  for(ind = 0; ind < len; ind++)
  {
    if(!ind)
    {
      min = array[ind];
    }
    else
    {
      if(min > array[ind])
      {
        min = array[ind];
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
  int arr[k];
  int index;

  for(index = 0; index < k; index++)
  {
    arr[index] = index;
  }

  permute(arr, k, 0);
}

void permute(int * array, int k, int index)
{
  if (index == k)
  {
    if(isStackSortable(array, k))
    {
      TreeNode * tr = Tree_build(array, k);
      Tree_printShape(tr);
      Tree_destroy(tr);
    }
  }

  int ind = index;
  for(; ind < k; ind++)
  {
    swap(&array[ind], &array[index]);
    permute(array, k, index + 1);
    swap(&array[ind], &array[index]);
  }
}

void swap(int * array, int * array2)
{
  int t = *array;
  *array = *array2;
  *array2 = t;
}
