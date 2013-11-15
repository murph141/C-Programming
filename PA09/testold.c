#include<stdio.h>
#include<stdlib.h>
#include "pa09.h"

HuffNode * huff_create(BITFILE * fptr, int bit)
{
  int done = 0;
  Stack * st = NULL;
  HuffNode * root = NULL;

  unsigned char info;

  while(!done)
  {
    if(bitget(fptr, bit) == '1')
    {
      info = bitget(fptr, bit);
      HuffNode * hf = huff_make(info);
      st = stack_push(st, hf); //getByte / getBit
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

BITFILE * bitopen(char * file)
{
  FILE * fptr = fopen(file, "rb");

  if(fptr == NULL)
  {
    printf("Memory allocated incorrectly (bitopen function)\n");
    return NULL;
  }

  BITFILE * bptr = malloc(sizeof(BITFILE));
  bptr -> fp = fptr;
  bptr -> byte = 0;
  bptr -> remaining = 0;

  return bptr;
}

void bitclose(BITFILE * bptr)
{
  if(bptr == NULL)
  {
    return;
  }

  fclose(bptr -> fp);
  free(bptr);
}

int bitget(BITFILE * bptr, int bit)
{
  int i;
  int f;
  int d = 0;

  if(bit)
  {
    f = 1;
  }
  else
  {
    f = 8;
  }

  for(i = 0; i < f; i++)
  {
    if(bptr -> remaining == 0)
    {
      if(fread(&(bptr -> byte), 1, 1, bptr -> fp) == 1)
      {
        bptr -> remaining = 0;
      }
    }

    if(bptr -> remaining == 0)
    {
      return -1;
    }

    int pos = (bptr -> remaining) - 1;
    unsigned char mask = 1 << pos;
    unsigned char ret = (bptr -> byte) & mask;
    ret = ret >> pos;
    bptr -> remaining -= 1;

    if(!bit)
    {
      if(ret < 0)
      {
        return -1;
      }
      d = d << 1;
      d = d | ret;
    }
    else
    {
      d = ret;
    }
  }
  printf("%d\n", d);
  return d;
}
