#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int main()
{
  avl_node root;
  init_avl(&root);
  insert(&root, 33); 
  insert(&root, 13); 
  insert(&root, 9); 
  insert(&root, 8); 
  insert(&root, 11); 
  insert(&root, 53); 
  insert(&root, 61); 
  insert(&root, 21); 
  printf("\nInorder\n");
  inorder(root);
  return 0;
}