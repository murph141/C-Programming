#include<stdio.h>
#include<stdlib.h>
#include "pa09.h"

HuffNode * huff_create(FILE * fptr)
{
  Stack * st = NULL;

  HuffNode * hf = NULL;
  HuffNode * pointer = NULL;

  unsigned char info;

  while(!feof(fptr))
  {
    if(fgetc(fptr) == 49)
    {
      info = fgetc(fptr);
      printf("%c\n", info);
      hf = huff_make(info);
      st = stack_push(st, hf); //getByte / getBit
    }
    else
    {
      pointer = st -> node;
      //A is a huffnode pointer

      if(st == NULL)
      {
        return pointer;
      }
      else
      {
        // pop the stack
      }
    }
  }
  return hf;
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
}


HuffNode * huff_make(int val)
{
  HuffNode * hf = malloc(sizeof(HuffNode));

  if(hf == NULL)
  {
    printf("Memory allocated incorrectly (create function)\n");
    return NULL;
  }

  hf -> value = val;
  hf -> left = NULL;
  hf -> right = NULL;

  return hf;
}


Stack * stack_push(Stack * st, HuffNode * hf)
{
  Stack * newnode = stack_create(hf);
  newnode -> next = NULL;

  return newnode;
}


Stack * stack_create(HuffNode * hf)
{
  Stack * st;
  st = malloc(sizeof(Stack));

  if(st == NULL)
  {
    printf("Memory allocated incorrectly (stack_create function)\n");
    return NULL;
  }

  st -> node = hf;
  st -> next = NULL;

  return st;
}
