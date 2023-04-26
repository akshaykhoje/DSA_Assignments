#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int main()
{
  avl_node root;
  init_avl(&root);
  // insert(&root, 33); 
  // insert(&root, 13); 
  // insert(&root, 9); 
  // insert(&root, 8); 
  // insert(&root, 11); 
  // insert(&root, 53); 
  // insert(&root, 61); 
  // insert(&root, 21);
  insert(&root, 178); 
  insert(&root, 32); 
  insert(&root, 59); 
  insert(&root, 205); 
  insert(&root, 210); 
  insert(&root, 80); 
  insert(&root, 75); 
  insert(&root, 66); 
  insert(&root, 100); 
  insert(&root, 125); 
  insert(&root, 10); 
  insert(&root, 15); 
  insert(&root, 108); 
  insert(&root, 84); 

  printf("\nInorder\n");
  inorder(root);
  return 0;
}