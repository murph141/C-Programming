
#include "pa03.h"
#include <stdio.h>
#include <stdlib.h>
int searchfx(int *, int, int, int, int);
void swapvalues(int *, int *);

/*
 * This function swaps the values of the upper
 * and lower values in the quicksort that are
 * provided to it.
*/

void swapvalues(int * value1, int * value2)
{
  int temp; //Temporary variable to swap values
  temp = *value1;
  *value1 = *value2;
  *value2 = temp;
}

/**
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numberOfIntegers: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * You do NOT know how many integers are in the file until you have
 * read it. Once you know how many integers there are, you can modify
 * the "numberOfIntegers" variable. (Note that this is a pointer, not
 * an integer) You must allocate memory to store the integers.
 * 
 * Once memory is allocated to store the integers, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek".
 * 
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read integeres is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * The allocated memory will be released in pa03.c. You do not need to
 * worry about releasing memory.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readIntegers(const char * filename, int * numberOfIntegers)
{
  int temp = 0; //Used to temporarily store the values that are input from the file
  int num; //Used as a counter variable when assigning values to the allocated array arr
  int * arr; //Array that will be allocated once values are passed in
  FILE * pFile;
  pFile = fopen(filename, "r"); //Open the file for reading

  if(pFile == NULL)
  {
    arr = NULL;
  }

  while(fscanf(pFile, "%d", &temp) == 1)
  {
    (*numberOfIntegers)++;
  }

  arr = malloc(sizeof(int) * (*numberOfIntegers)); //Allocate space according to the file size

  if(!fseek(pFile, 0, SEEK_SET))
  {
    num = 0;

    while(fscanf(pFile, "%d", &arr[num]) == 1)
    {
      num++;
    }
  }
  else
  {
    arr = NULL;
  }

  fclose(pFile); //Close the file

  return arr;
}

/**
 * Sort an (ascending) array of integers
 *
 * Arguments:
 * arr    The array to search
 * length Number of elements in the array
 *
 * Uses "quicksort" to sort "arr".  Use the first element of the array
 * as the pivot.  
 *
 * Your solution MUST use recursive function (or functions)
 * 
 * quicksort works in the following way: 
 * 
 * find an element in the array (this element is called the
 * pivot). 
 *
 * rearrange the array's elements into two parts: the part smaller
 * than this pivot and the part greater than this pivot; make the pivot
 * the element between these two parts
 * 
 * sort the first and the second parts separately by repeating the 
 * procedure described above
 * 
 * You will receive no point if you use any other sorting algorithm.
 * You cannot use selection sort, merge sort, or bubble sort.
 * 
 * Some students are fascinated by the name of bubble sort.  In
 * reality, bubble sort is rarely used because it is slow.  It is a
 * mystery why some students (or even professors) like bubble sort.
 * Other than the funny name, bubble sort has nothing special and is
 * inefficient, in both asymptotic complexity and the amount of data
 * movement.  There are many algorithms much better than bubble sort.
 * You would not lose anything if you do not know (or forget) bubble
 * sort.
 *
 */
void sort(int * arr, int length)
{
  int pivot = 0; //Use first position as pivot position
  int lower = 0;
  int upper = length - 1;

  if(length >= 2)
  {
    while(lower < upper)
    {
      while(arr[lower] < arr[pivot])
      {
        lower++;
      }
      while(arr[upper] > arr[pivot])
      {
        upper--;
      }
      swapvalues(&arr[lower], &arr[upper]);
    }
    sort(arr, lower); //Sort the lower half of the array first
    sort(&arr[lower + 1], length - lower - 1); //Sort the upper half of the array after
  }
}

/**
 * Use binary search to find 'key' in a sorted array of integers
 *
 * Arguments:
 * 
 * arr The array to search. Must be sorted ascending.  You do not need
 *        to check. This array is from the result of your sort
 *        function. Make sure your sort function is correct before you
 *        start writing this function.
 *
 * length Number of elements in the array
 * key    Value to search for in arr
 *
 * Returns:
 * The index of 'key', or -1 if key is not found.
 *
 * Since the array is sorted, you can quickly discard many elements by
 * comparing the key and the element at the center of the array. If
 * the key is the same as this element, you have found the index.  If
 * the key is greater than this element, you can discard the first
 * half of the array.  If the key is smaller, you can discard the
 * second half of the array.  Now you have only half of the array to
 * search.  Continue this procedure until either you find the index or
 * it is impossible to find a match.
 * 
 * Your solution MUST use recursive function (or functions)
 *
 * Don't forget that arrays are 'zero-indexed'. Also, you must
 * use a binary search to pass this question.
 * 
 * You will receive no point if you do the following because it is not
 * binary search.  This is called linear search because it checks
 * every element.
 *
 * int ind;
 * for (ind = 0; ind < length; ind ++)
 * {
 *    if (arr[ind] == key)
 *    {
 *       return ind;
 *    }
 * }
 * return -1;
 */

int search(int * arr, int length, int key)
{
  int a; //Variable used to take returning function value
  a = searchfx(arr, length, key, 0 , length - 1);

  return a;
}

/*
 * This function uses a recursive binary search
 * that takes an array, its length, a value to find,
 * and a lower and upper bound.  The lower and upper
 * bounds are present because the functions needs to 
 * keep track of the values that it has gone through
*/

int searchfx(int * arr, int length, int key, int low, int high)
{ 
  int mid = (low + high) / 2; //Middle value is the average of the lower and higher values
  int test; //Test is used to return values recursively so when the value is found, it will keep being returned

  if(high < low)
  {
    // Check whether you have reached the end of your array
    // Two possible outcomes, value present or not present
    if(arr[mid] == key)
    {
      test = mid;
    }
    else
    {
      test = -1;
    }
  }
  //Check if mid is the value
  else if(arr[mid] == key)
  {
    test = mid;
  }
  //If key is greater than the mid, recall function
  else if(key > arr[mid])
  {
    test = searchfx(arr, high - mid, key, mid + 1, high);
  }
  //If key is less than mid, recall function
  else if(key < arr[mid])
  {
    test = searchfx(arr, mid, key, low, mid - 1);
  }
  
  return test; //Return test recursively
}
