#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


void init_avl(avl_node *t)
{
  *t = NULL;
  return;
}


void insert(avl_node *t, int n)
{
  node *nn = (node *)malloc(sizeof(node));
  nn->data = n;
  nn->left = NULL;
  nn->right = NULL;

  if (!(*t))
  {
    *t = nn;
    return;
  }

  avl_node p, q;
  q = NULL;
  p = *t;
  while (p)
  {
    q = p; // hold the back pointer
    if (n < p->data)
      p = p->left;
    else if (n > p->data)
      p = p->right;
    else
      return;
  }

  nn->parent = q;
  if (n < q->data)
    q->left = nn;
  else
    q->right = nn;

  reassign_bf(q);     // reassign the balance factor of q

  avl_node unbal = NULL;
  unbal = imbalanced_node(q);
  do
  {
    if (!unbal)
      return;

    avl_node parent_of_unbal = unbal->parent;

    if (unbal->bf == 2 && unbal->left->bf == 1)
      LL_rotation(t, &unbal);
    else if (unbal->bf == 2 && unbal->left->bf == -1)
      LR_rotation(t, &unbal);
    else if (unbal->bf == 2 && unbal->right->bf == 1)
      RR_rotation(t, &unbal);
    else if (unbal->bf == 2 && unbal->right->bf == -1)
      RL_rotation(t, &unbal);

    reassign_bf(parent_of_unbal);
    unbal = imbalanced_node(parent_of_unbal);

  } while (unbal);

  return;
}


int height(avl_node t)
{
  if (!t)
    return -1;
  int lh = height(t->left);
  int rh = height(t->right);

  return lh > rh ? lh + 1 : rh + 1;
}


void reassign_bf(avl_node t)
{
  if (!t)
    return;
  t->bf = height(t->left) - height(t->right);

  reassign_bf(t->parent);     //go all the way to the top of the tree balancing each node on its way
}


avl_node imbalanced_node(avl_node t)
{ 
  if (!t)
    return NULL;  
  
  if (t->bf >= 2 || t->bf <= -2)
    return t;
  
  return imbalanced_node(t->parent);
}


// ROTATIONS

void LL_rotation(avl_node *t, avl_node *n)
{
  avl_node A = *n;
  avl_node B = (*n)->left;
  avl_node BR = B->right;
  B->right = A;
  A->left = BR;
  B->parent = A->parent;
  
  if (BR)
  {
    BR->parent = A;
  }
  A->parent = B;
  B->bf = 0;
  A->bf = 0;
  if (*t == A)
  {
    *t = B;
    return;
  }
  if (B->parent->left == A)
  {
    B->parent->left = B;
  }
  else
    B->parent->right = B;
  return;
}


void RR_rotation(avl_node *t, avl_node *n)
{
  avl_node A = (*n);
  avl_node B = ((*n)->right);
  avl_node BL = B->left;
  B->left = A;
  A->right = BL;
  B->parent = A->parent;
  if (BL)
    BL->parent = A;
  A->parent = B;
  B->bf = 0;
  A->bf = 0;
  if ((*t) == A)
  {
    (*t) = B;
    return;
  }
  if (B->parent->left == A)
    B->parent->left = B;
  else
    B->parent->right = B;
  return;
}


void LR_rotation(avl_node *t, avl_node *n)
{
  RR_rotation(t, &(*n)->left);
  LL_rotation(t, n);
}

void RL_rotation(avl_node *t, avl_node *n)
{
  LL_rotation(t, &(*n)->right);
  RR_rotation(t, n);
}


void inorder(avl_node t)
{
  if (!t)
    return;

  inorder(t->left);
  printf("Data : %d, bf : %d \n", t->data, t->bf);
  inorder(t->right);
}



