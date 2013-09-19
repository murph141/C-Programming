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

//----------------------------
#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>

void partition(int, int *, int);

void partitionInc(int, int *, int);
int isIncreasing(int *);

void partitionDec(int, int *, int);
int isDecreasing(int *);

void partOdd(int, int*, int);
int isOdd(int *);

void partEven(int, int*, int);
int isEven(int *);

void partOddEven(int, int*, int);
int isOddEven(int *);

void partPrime(int, int *, int);
int isPrime(int *);

void printArray(int, int *);
int sumArray(int *);
//-----------------------------


int sumArray(int * arr)
{
  int i = 0;
  int sum = 0;

  while(arr[i] != '\0')
  {
    sum += arr[i++];
  }

  return sum;
}


void printArray(int value, int * arr)
{
  int i = 0;
  printf("= ");
  while(arr[i] != 0)
  {
    printf("%d", arr[i++]);

    if(arr[i] != 0)
    {
      printf(" + ");
    }
  }
  printf("\n");
}


//Regular Partitioning
void partition(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partition(value - 1, arr, original);
        }
      }
      else
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
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
  int arr[MAXLENGTH] = {0};

  printf("partitionAll %d\n", value);

  partition(value, arr, value);
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
  int arr[MAXLENGTH] = {0};

  printf("partitionIncreasing %d\n", value);

  partitionInc(value, arr, value);
}



void partitionInc(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partitionInc(value - 1, arr, original);
        }
      }
      else if(isIncreasing(arr))
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
}


//Checks whether the numbers are increasing
int isIncreasing(int * arr)
{
  int i = 0;
  int j = 1;

  while(arr[i + 1] != 0)
  {
    if(arr[i] < arr[i + 1])
    {
      j *= 1;
    }
    else
    {
      j *= 0;
    }
    i++;
  }

  return j;
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
  int arr[MAXLENGTH] = {0};

  printf("partitionDecreasing %d\n", value);

  partitionDec(value, arr, value);
}


void partitionDec(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partitionDec(value - 1, arr, original);
        }
      }
      else if(isDecreasing(arr))
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
}


//Checks whether the numbers are increasing
int isDecreasing(int * arr)
{
  int i = 0;
  int j = 1;

  while(arr[i + 1] != 0)
  {
    if(arr[i] > arr[i + 1])
    {
      j *= 1;
    }
    else
    {
      j *= 0;
    }
    i++;
  }

  return j;
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
  int arr[MAXLENGTH] = {0};

  printf("partitionOdd %d\n", value);

  partOdd(value, arr, value);
}


void partOdd(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partOdd(value - 1, arr, original);
        }
      }
      else if(isOdd(arr))
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
}


//Checks whether the numbers are increasing
int isOdd(int * arr)
{
  int i = 0;
  int j = 1;

  while(arr[i] != 0)
  {
    if(arr[i] % 2)
    {
      j *= 1;
    }
    else
    {
      j *= 0;
    }
    i++;
  }

  return j;
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
  int arr[MAXLENGTH] = {0};

  printf("partitionEven %d\n", value);

  partEven(value, arr, value);
}


void partEven(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partEven(value - 1, arr, original);
        }
      }
      else if(isEven(arr))
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
}


//Checks whether the numbers are increasing
int isEven(int * arr)
{
  int i = 0;
  int j = 1;

  while(arr[i] != 0)
  {
    if(arr[i] % 2 == 0)
    {
      j *= 1;
    }
    else
    {
      j *= 0;
    }
    i++;
  }

  return j;
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
  int arr[MAXLENGTH] = {0};

  printf("partitionOddAndEven %d\n", value);

  partOddEven(value, arr, value);
}


void partOddEven(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partOddEven(value - 1, arr, original);
        }
      }
      else if(isOddEven(arr))
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
}


//Checks whether the numbers are increasing
int isOddEven(int * arr)
{
  int i = 0;
  int j = 1;

  if(arr[0] % 2)
  {
    while(arr[i + 1] != 0)
    {
      if(arr[i] % 2 != arr[i + 1] % 2)
      {
        j *= 1;
      }
      else
      {
        j *= 0;
      }
      i++;
    }
  }
  else
  {
    j = 0;
  }

  return j;
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
  int arr[MAXLENGTH] = {0};

  printf("partitionPrime %d\n", value);

  partPrime(value, arr, value);
}


void partPrime(int value, int * arr, int original)
{
  int i;

  if(value >= 1)
  {
    for(i = 1; i <= value; i++)
    {
      arr[original - value] = i;

      if(sumArray(arr) != original)
      {
        if(value > 1 && sumArray(arr) < original)
        {
          partPrime(value - 1, arr, original);
        }
      }
      else if(isPrime(arr))
      {
        printArray(original, arr);
      }

      arr[original - i] = 0; 
    }
  }
}

int isPrime(int * arr)
{
  int j;
  int i = 0;
  int k = 1;

  if(arr[1] == 0)
  {
    k = 0;
  }

  while(arr[i] != 0 && k == 1)
  {
    if(arr[i] == 1)
    {
      k = 0;
    }

    for(j = 2; j < arr[i]; j++)
    {
      if(arr[i] % j == 0)
      {
        k = 0;
      }
    }
    i++;
  }

  return k;
}
