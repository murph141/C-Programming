#include<stdio.h>
#include<stdlib.h>
#include "pa09.h"


int main(int argc, char * * argv)
{
  if(argc != 3)
  {
    printf("Usage: ./pa09 <input filename> <output filename>\n");
    return EXIT_FAILURE;
  }

  FILE * fptr = fopen(argv[1], "rb");
  FILE * fwrite = fopen(argv[2], "wb");

  if(fptr == NULL || fwrite == NULL)
  {
    printf("File opened unsuccessfully\n");
    return EXIT_FAILURE;
  }

  HuffNode * tree = NULL;
  //tree = malloc(sizeof(HuffNode));

  tree = huff_create(fptr);

  fclose(fptr);
  return EXIT_SUCCESS;
}
