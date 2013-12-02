#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
  int value; 
  struct _huffnode * left;
  struct _huffnode * right;
} HuffNode; //Treenode

typedef struct _stack {
  struct _stack * next;
  HuffNode * node;
} Stack; //StackNode


void huff_print(HuffNode *, FILE *);
HuffNode * huff_create(FILE *, int);
HuffNode * huff_make(int);
Stack * stack_push(Stack *, HuffNode *);
Stack * stack_create(HuffNode *);
Stack * stack_pop(Stack *);

#endif
