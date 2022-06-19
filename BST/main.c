#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main()
{
  BST t1;
  init_bst(&t1);
  insert_node(&t1, 5);
  insert_node(&t1, 23);
  insert_node(&t1, -21);
  insert_node(&t1, -6);
  insert_node(&t1, 82);
  insert_node(&t1, 182);
  insert_node(&t1, 7);
  printf("\nInorder \n");
  inorder(t1);
  printf("\nPreorder \n");
  preorder(t1);
  printf("\nPostorder \n");
  postorder(t1);
  // remove_node(&t1, 23);
  // printf("\ninorder\n");
  // inorder(t1);
  // printf("\ninorder\n");
  // remove_node_iterative(&t1, 82);
  // inorder(t1);
  // node *ptr = search(t1, 23);
  // if (ptr)
  //   printf("\ndata : %d ", ptr->data);
  // else
  //   printf("\nKey not found!\n");
  printf("\nDisplay level\n");
  display_level(t1, 2);

  return 0;
}

