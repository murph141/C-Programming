#include<stdio.h>
#include<stdlib.h>


int main(int argc, char * * argv)
{
  if(argc != 2)
  {
    printf("Usage: ./pa09 <input filename> <output filename>\n");
  }

  FILE * fptr = NULL;
  file = fopen(argc[0], 'r');


  if(fptr == NULL)
  {
    printf("File opened incorrectly\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
