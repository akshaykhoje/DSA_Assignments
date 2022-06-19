typedef struct node{
  int data, i, j;
  struct node *down, *right;
} node;


typedef struct sparse{
  int r, c;
  node **row, **col;
} sparse;