#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"
#define MAXIMUM_LENGTH 80

//Declare the two comparison functions

int compstr(const void *, const void *);
int compint(const void *, const void *);


/*
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numInteger: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fscanf
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
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readInteger(char * filename, int * numInteger)
{
  int * arr; //Array that will store the values
  int ind = 0; //Index value
  FILE * fptr = fopen(filename, "r"); //Open the file for reading
  int buffer; //Used to temporarily store the values of fscanf

  if(fptr == NULL)
  {
    return NULL; //Return null if the file has problems being read/opened
  }

  while(fscanf(fptr, "%d", &buffer) == 1)
  {
    (*numInteger)++; //Increment numInteger each time a line is read in
  }

  fseek(fptr, 0 , SEEK_SET);

  arr = malloc(sizeof(int) * (*numInteger)); //Allocate based on the size of the file

  while(fscanf(fptr, "%d", &arr[ind]) == 1)
  {
    ind++;
  }

  fclose(fptr); //Close the file

  return arr; //Return the array
}

/* ----------------------------------------------- */

/*
 * Read a file of strings. This is similar to readInteger. However,
 * each string is an array of characters. The function needs to
 * allocate memory for an array of strings, i.e., array of arrays of
 * characters. In other words, this is a two-dimensional array (thus,
 * char **).
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of strings (one
 * per line)
 * 
 * numString: pointer to store the number of strings in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of strings from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fgets. 
 * 
 * Remember that an array of strings is a two-dimensional array of
 * characters
 *
 * You do NOT know how many strings are in the file until you have
 * read it. Once you know how many strings there are, you can modify
 * the "numberOfStrings" variable. (Note that this is a pointer, not
 * an string) You must allocate memory to store the strings.
 * 
 * Once memory is allocated to store the strings, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read stringes is to use the "fscanf" function.  It is
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
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of strings in the file.  For example, if
 * you write this
 *
 * char array[10000];
 * 
 *
 */

char * * readString(char * filename, int * numString)
{
  char buffer[MAXIMUM_LENGTH]; //Make an array that will hold the values of the string being read in
  int ind = 0; //Index value
  char * * strArr; //The array that will be returned at the end of the function
  FILE * fptr = fopen(filename, "r"); //Open the file for reading

  if(fptr == NULL)
  {
    return NULL; //If the file can't be read/opened, return null
  }

  while(fgets(buffer, MAXIMUM_LENGTH, fptr) != NULL)
  {
    (*numString)++; //Increment numString for each time a line is read in
  }

  fseek(fptr, 0, SEEK_SET); //Reset file to the beginning

  strArr = malloc(sizeof(char *) * (*numString)); //Allocate space for the first dimension of the array

  while(fgets(buffer, MAXIMUM_LENGTH, fptr) != NULL)
  {
    //Allocate space for the array in the second dimension based on the number of characters that are read on each line
    strArr[ind] = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(strArr[ind], buffer); //Copy the buffer that was read in to the string array
    ind++;
  }

  fclose(fptr); //Close the file

  return strArr; //Return the array of the array of characters
}

/* ----------------------------------------------- */
/*
 * print an array of integers, one integer per line
 */
void printInteger(int * arrInteger, int numInteger)
{
  int ind; //Index value

  for(ind = 0; ind < numInteger; ind++)
  {
    printf("%d\n", arrInteger[ind]); //Print an integer on a separate line numInteger times
  }
}

/* ----------------------------------------------- */
/*
 * print an array of strings, one string per line
 *
 * Hint: printf("%s" ... can print a string
 */
void printString(char * * arrString, int numString)
{
  int ind; //Index value

  for(ind = 0; ind < numString; ind++)
  {
    int len = strlen(arrString[ind]);

    printf("%s", arrString[ind]); //Print a string

    if(arrString[ind][len - 1] != '\n' || len == 0)
    {
      printf("\n");
    }
  }
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of integers
 */
void freeInteger(int * arrInteger, int numInteger)
{
  free(arrInteger); //Free the array of integers
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of strings
 *
 * Hint: an array of strings is a two-dimensional array of characters
 */
void freeString(char * * arrString, int numString)
{
  int ind; //Index value

  for(ind = 0; ind < numString; ind++)
  {
    free(arrString[ind]); //Free the individual indicies of the string array
  }

  free(arrString); //Free the original the array, the array that contains the number of lines that are read in
}

/* ----------------------------------------------- */
/*
 * Write integers to a file, one integer per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrInteger: an array of integers
 * numInteger: the number of integers 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %d
 *
 */

int saveInteger(char * filename, int * arrInteger, int numInteger)
{
  FILE * fptr = fopen(filename, "w"); //Open the file for writing
  int ind; //Index value

  if(fptr == NULL)
  {
    return 0; //If the file can't be opened, return a 0 to show an error occured
  }

  for(ind = 0; ind < numInteger; ind++)
  {
    if(fprintf(fptr, "%d\n", arrInteger[ind]) < 0)
    {
      fclose(fptr); //Close the file
      return 0; //Return an error value
    }
  }

  fclose(fptr); //Close the file
  return 1; //Return 1 to signify success
}

/* ----------------------------------------------- */
/*
 * Write strings to a file, one string per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrString: an array of strings
 * numString: the number of strings 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %s
 *
 */

int saveString(char * filename, char * * arrString, int numString)
{
  FILE * fptr = fopen(filename, "w"); //Open the file for writing
  int ind; //Index value

  if(fptr == NULL)
  {
    return 0; //If the file can't be opened or written to, return 0 to signify an error
  }

  for(ind = 0; ind < numString; ind++)
  {
    if(fprintf(fptr, "%s", arrString[ind])  < 0)
    {
      fclose(fptr); //Close the file
      return 0; //Return a 0 to signify an error
    }
  }

  fclose(fptr); //Close the file
  return 1; //Return a 1 to signify success
}

/* ----------------------------------------------- */
/*
 * sort an arry of integers by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 */

void sortInteger(int * arrInteger, int numInteger)
{
  qsort(arrInteger, numInteger, sizeof(int), compint); //Call the qsort function with the function to compare integers
}


/* ----------------------------------------------- */
/*
 * sort an arry of strings by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 * Hint: use strcmp in the comparison function
 *
 */


void sortString(char * * arrString, int numString)
{
  qsort(arrString, numString, sizeof(char *), compstr); //Call the qsort function with the function to compare strings (chars)
}


int compstr(const void * s1, const void * s2)
{
  char * str1 = *(char **) s1; //Cast type the array of array of chars and pull the value from it
  char * str2 = *(char **) s2; //Cast type the array of array of chars and pull the value from it

  return strcmp(str1, str2); //Return the value of the string comparison function from string.h
}


int compint(const void * i1, const void * i2)
{
  int int1 = * (int *) i1; //Cast type the integer pointer and take the value from it
  int int2 = * (int *) i2; //Cast type the integer pointer and take the value from it

  if(int1 < int2)
  {
    return -1; //Return a negative number if the first integer is less than the second integer
  }
  if(int1 > int2)
  {
    return 1; //Return a positive number if the first integer is greater than the second integer
  }

  return 0; //Return a zero if the two numbers are equal
}
