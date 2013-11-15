#include<stdio.h>
#include<stdlib.h>
#include "pa09.h"

HuffNode * huff_create(FILE * fptr, int bit)
{
  int done = 0;
  int cmdloc = 0;
  Stack * st = NULL;
  HuffNode * root = NULL;

  unsigned char info;
  unsigned char masks[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

  while(!done)
  {
    if(!bit)
    {
      if(fgetc(fptr) == 49)
      {
        info = fgetc(fptr);
        HuffNode * hf = huff_make(info);
        st = stack_push(st, hf);
      }
      else
      {
        HuffNode * A = st -> node;
        st = stack_pop(st);

        if(st == NULL)
        {
          root = A;
          done = 1;
        }
        else
        {
          HuffNode * B = st -> node;
          st = stack_pop(st);
          HuffNode * C = malloc(sizeof(HuffNode));
          C -> value = ' ';
          C -> right = A;
          C -> left = B;
          st = stack_push(st, C);
        }
      }
    }
    else
    {
      if((fgetc(fptr) & masks[cmdloc]) != 0)
      {
        info = fgetc(fptr) & masks[cmdloc];
        info = info >> cmdloc;
        
        cmdloc = (cmdloc + 2) % 8;

        HuffNode * hf = huff_make(info);
        st = stack_push(st, hf);
      }
      else
      {
        HuffNode * A = st -> node;
        st = stack_pop(st);

        cmdloc = (cmdloc + 1) % 8;

        if(st == NULL)
        {
          root = A;
          done = 1;
        }
        else
        {
          HuffNode * B = st -> node;
          st = stack_pop(st);
          HuffNode * C = malloc(sizeof(HuffNode));
          C -> value = ' ';
          C -> right = A;
          C -> left = B;
          st = stack_push(st, C);
        }
      }
    }
  }

  return root;
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
  newnode -> next = st;

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

Stack * stack_pop(Stack * st)
{
  if(st == NULL)
  {
    return NULL;
  }

  Stack * b = st -> next;
  free(st);
  return b;
}
