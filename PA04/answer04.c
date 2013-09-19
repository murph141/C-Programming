/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void partition(int, int *, int);
void partInc(int, int *, int, int);
void partDec(int, int *, int, int);
void partOdd(int, int *, int);
void partEven(int, int *, int);
void partOaE(int, int *, int, int);
void partPrime(int, int *, int);
void printArray(int *, int);
int isPrime(int);

//This function is used to print the array values
void printArray(int * arr, int ind)
{
  int i = 0;
  printf("= "); //Formatting
  while(ind)
  {
    printf("%d", arr[i++]);

    ind--;

    if(ind)
    {
      printf(" + ");
    }
  }

  printf("\n"); //Formatting
}


/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */


void partitionAll(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionAll %d\n", value);

  partition(value, arr, 0); //Initial index is 0
}


void partition(int value, int * arr, int ind)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  for(i = 1; i <= value; i++)
  {
    arr[ind] = i;

    partition(value - i, arr, ind + 1);
  }
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionIncreasing(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionIncreasing %d\n", value);

  partInc(value, arr, 0, 1); //Initial index is 0 and initial starting point is 1
}

void partInc(int value, int * arr, int ind, int start)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  //Start at 1 initially since it is the lowest number
  for(i = start; i <= value; i++)
  {
    arr[ind] = i;

    partInc(value - i, arr, ind + 1, i + 1);
  }
}
/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionDecreasing %d\n", value);

  partDec(value, arr, 0, value); //Initial index is 0 and initial starting point is the value being input
}


void partDec(int value, int * arr, int ind, int start)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  //Decrement array since we are starting at the highest possible number and going down
  for(i = start; i > 0; i--)
  {
    arr[ind] = i;

    partDec(value - i, arr, ind + 1, i - 1);
  }
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOdd(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionOdd %d\n", value);

  partOdd(value, arr, 0); //Intial starting index is 0
}


void partOdd(int value, int * arr, int ind)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  //Start at 1, an odd number, and increment by 2 to stay on odd numbers
  for(i = 1; i <= value; i += 2)
  {
    arr[ind] = i;

    partOdd(value - i, arr, ind + 1);
  }
}
/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionEven %d\n", value);

  partEven(value, arr, 0); //Initial starting index is 0
}


void partEven(int value, int * arr, int ind)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  //Start at 2, the lowest even number, and increment by 2 to stay on even numbers
  for(i = 2; i <= value; i += 2)
  {
    arr[ind] = i;

    partEven(value - i, arr, ind + 1);
  }
}
/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOddAndEven(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionOddAndEven %d\n", value);

  partOaE(value, arr, 0, 1); //Initial starting index is 0 and the values start on odd numbers
}

void partOaE(int value, int * arr, int ind, int odd)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  //Perform the odd loop if we are on an odd number
  if(odd)
  {
    for(i = 1; i <= value; i += 2)
    {
      arr[ind] = i;

      partOaE(value - i, arr, ind + 1, !odd); //Odd is opposite of what it was before
    }
  }
  //Otherwise, perform the even loop
  else
  {
    for(i = 2; i <= value; i += 2)
    {
      arr[ind] = i;

      partOaE(value - i, arr, ind + 1, !odd); //Odd is opposite of what is was before
    }
  }
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */



void partitionPrime(int value)
{
  int arr[MAXLENGTH] = {0}; //Make array values all 0

  printf("partitionPrime %d\n", value);

  partPrime(value, arr, 0); //Intial starting index is 0
}

void partPrime(int value, int * arr, int ind)
{
  int i;

  if(value == 0)
  {
    printArray(arr, ind);
    return;
  }

  for(i = 2; i <= value; i++)
  {
    if(isPrime(i)) //Only recall the function and place values if i is prime
    {
      arr[ind] = i;

      partPrime(value - i, arr, ind + 1);
    }
  }
}

int isPrime(int i)
{
  int j = 1;
  int k;

  //Check to make sure i is only divisible by itself
  for(k = 2; k < i; k++)
  {
    if(i % k == 0 && i != k)
    {
      j = 0;
    }
  }

  return j;
}
