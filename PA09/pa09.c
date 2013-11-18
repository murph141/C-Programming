#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pa09.h"


int main(int argc, char * * argv)
{
  int bit; //Determines if the file is a character file or a binary file

  //Call if three arguments aren't given
  if(argc != 3)
  {
    printf("Usage: ./pa09 <input filename> <output filename>\n");
    return EXIT_FAILURE;
  }

  //Check if the file is a character or binary file
  if(strstr(argv[1], "bit"))
  {
    bit = 1;
  }
  else
  {
    bit = 0;
  }

  //Open the two files
  FILE * fptr = fopen(argv[1], "rb");
  FILE * fwrite = fopen(argv[2], "wb");

  //Call if either of the files aren't opened correctly
  if(fptr == NULL || fwrite == NULL)
  {
    printf("File opened unsuccessfully\n");
    return EXIT_FAILURE;
  }

  HuffNode * tree = NULL; //Create a new hufftree node

  tree = huff_create(fptr, bit); //Set the tree equal to the output of the huff_create function

  fclose(fptr); //Close the input file

  huff_print(tree, fwrite); //Print the tree contents to the output file

  fclose(fwrite); //Close the output file

  return EXIT_SUCCESS;
}
