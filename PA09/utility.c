#include<stdio.h>
#include<stdlib.h>
#include "pa09.h"

HuffNode * huff_create(FILE * fptr, int bit)
{
  int done = 0; //Tell the program when it has completed
  int cmdloc = 0; //Location of the determining bit
  Stack * st = NULL;
  HuffNode * root = NULL;

  int first = 1; //For use with the bit part of this function, determines if the loop has just started
  unsigned char info; //Hold values
  unsigned char info2; //Hold values
  unsigned char masks[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}; //Bit locations

  while(!done)
  {
    if(!bit)
    {
      if(fgetc(fptr) == 49)
      {
        info = fgetc(fptr); //Get value
        HuffNode * hf = huff_make(info); //Make a huffman tree
        st = stack_push(st, hf); //Push the tree on to the stack
      }
      else
      {
        HuffNode * A = st -> node; //Set the huffman tree as the node of the stack
        st = stack_pop(st); //Pop the first item off of the stack

        if(st == NULL)
        {
          root = A; //Set the final tree to A
          done = 1; //Tell the loop to exit
        }
        else
        {
          HuffNode * B = st -> node; //Set the huffman tree as the node of the stack
          st = stack_pop(st); //Pop an item off of the stack
          HuffNode * C = malloc(sizeof(HuffNode)); //Allocate space for the huffman tree
          C -> value = ' '; //Set the value to an arbitrary character (Space)
          C -> right = A; //Set the right side to the first huffman tree
          C -> left = B; //Set the left side to the second huffman tree 
          st = stack_push(st, C); //Push an item off of the stack
        }
      }
    }
    else
    {
      //Called on first iteration of this loop
      if(first)
      {
        info = fgetc(fptr); //Get the first byte
        first = 0; //Loop has been called
      }

      if((info & masks[cmdloc]) != 0)
      {
        info2 = fgetc(fptr); //Get the second byte
        info <<= (cmdloc + 1); //Left shift by cmdloc + 1
        info = (info2 >> (7 - cmdloc)) | info; //Info is equal to the left shifted value and the right shifted value

        HuffNode * hf = huff_make(info); //Make a new huffman tree
        st = stack_push(st, hf); //Push an item off of the stack

        cmdloc = (cmdloc + 1) % 8; //Increment cmdloc

        if(!cmdloc)
        {
          info2 = fgetc(fptr); //If cmdloc is at 0, get another byte of data
        }

        info = info2; //Set info to the next byte of data
      }
      else
      {
        HuffNode * A = st -> node; //Set the stack node equal to a huffman tree
        st = stack_pop(st); //Pop an item off of the stack

        cmdloc = (cmdloc + 1) % 8; //Increment cmdloc

        if(!cmdloc)
        {
          info2 = fgetc(fptr); //If cmdloc is at 0, get another byte of data
          info = info2; //Set info to he next byte of data
        }

        if(st == NULL)
        {
          root = A; //Set the root tree equal to A
          done = 1; //Tell the program that it is finished
        }
        else
        {
          HuffNode * B = st -> node; //Set the stack node equal to a huffman tree
          st = stack_pop(st); //Pop an item off of the stack
          HuffNode * C = malloc(sizeof(HuffNode)); //Allocate space for a huffman tree
          C -> value = ' '; //Set the value to an arbitrary value (Space)
          C -> right = A; //Set the right value equal to tree A
          C -> left = B; //Set the left value equal to tree B
          st = stack_push(st, C); //Push an item on to the stack
        }
      }
    }
  }
  return root; //Return the root tree
}


//Taken from tree.c
void huff_print(HuffNode * tree, FILE * fptr)
{
  // Base case: empty subtree
  if (tree == NULL)
  {
    return;
  }

  // Recursive case: post-order traversal

  // Visit left
  fprintf(fptr, "Left\n");
  huff_print(tree->left, fptr);
  fprintf(fptr, "Back\n");

  // Visit right
  fprintf(fptr, "Right\n");
  huff_print(tree->right, fptr);
  fprintf(fptr, "Back\n");

  // Visit node itself (only if leaf)
  if (tree->left == NULL && tree->right == NULL)
  {
    fprintf(fptr, "Leaf: %c\n", tree->value);
  }
  free(tree);
}


HuffNode * huff_make(int val)
{
  HuffNode * hf = malloc(sizeof(HuffNode)); //Allocate space for a huffman tree

  //Only called if memory is allocated incorrectly
  if(hf == NULL)
  {
    printf("Memory allocated incorrectly (create function)\n");
    return NULL;
  }

  hf -> value = val; //sSet the value equal to val
  hf -> left = NULL; //Set the left node to NULL
  hf -> right = NULL; //Set the right node to NULL

  return hf; //Return the huffman tree
}


Stack * stack_push(Stack * st, HuffNode * hf)
{
  Stack * newnode = stack_create(hf); //The newnode is equal to the return value of the stack create function
  newnode -> next = st; //The next stack is equal to the given stack

  return newnode; //Return the new node
}


Stack * stack_create(HuffNode * hf)
{
  Stack * st; 
  st = malloc(sizeof(Stack)); //Create a new stack node

  //Only called if memory is allocated incorrectly
  if(st == NULL)
  {
    printf("Memory allocated incorrectly (stack_create function)\n");
    return NULL;
  }

  st -> node = hf; //Set the node equal to the given huffman tree
  st -> next = NULL; //Set the next node to null

  return st; //Return the stack node
}

Stack * stack_pop(Stack * st)
{
  //If stack is empty, return NULL
  if(st == NULL)
  {
    return NULL;
  }

  Stack * b = st -> next; //Stack b is equal to the next stack 
  free(st); //Free the stack node
  return b; //Send stack b
}
