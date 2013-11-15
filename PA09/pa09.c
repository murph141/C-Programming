#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pa09.h"


int main(int argc, char * * argv)
{
  int bit;

  if(argc != 3)
  {
    printf("Usage: ./pa09 <input filename> <output filename>\n");
    return EXIT_FAILURE;
  }

  if(strstr(argv[1], "bit"))
  {
    bit = 1;
  }
  else
  {
    bit = 0;
  }

  FILE * fptr = fopen(argv[1], "rb");
  FILE * fwrite = fopen(argv[2], "wb");

  if(fptr == NULL || fwrite == NULL)
  {
    printf("File opened unsuccessfully\n");
    return EXIT_FAILURE;
  }

  HuffNode * tree = NULL;

  tree = huff_create(fptr, bit);

  fclose(fptr);

  huff_print(tree, fwrite);

  fclose(fwrite);

  return EXIT_SUCCESS;
}
