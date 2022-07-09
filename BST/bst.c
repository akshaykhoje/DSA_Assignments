#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

node *min_value_node(BST t);


void init_bst(BST *t)
{
  *t = NULL;
  return;
}


void insert_node(BST *t, int x)
{
  node *nn = (node *)malloc(sizeof(node));
  nn->data = x;
  nn->left = NULL;
  nn->right = NULL;

  if (!(*t))
    *t = nn;

  node *temp = *t;

  if (x < temp->data)
    insert_node(&(temp->left), x);

  else if (x > temp->data)
    insert_node(&(temp->right), x);

  else if (x == temp->data)
    return;
  return;
}


node *remove_node(BST *t, int d)
{
  node *temp = *t;

  if (temp == NULL)
    return temp;

  // if key to be deleted is smaller than the root's key
  if (d < temp->data)
    temp->left = remove_node(&(temp->left), d);

  // if key to be deleted is greater than the root's key
  else if (d > temp->data)
    temp->right = remove_node(&(temp->right), d);

  // if key is same as the root's key then delete this node
  else
  {
    // node with only one child
    if (temp->left == NULL)
    {
      node *p = temp->right;
      free(temp);
      return p;
    }
    else if (temp->right == NULL)
    {
      node *p = temp->left;
      free(temp);
      return p;
    }

    // node with two children, get the inorder successor
    node *p = min_value_node(temp->right);

    // copy the inorder successor's content to this node
    temp->data = p->data;

    // delete the inorder successor
    temp->right = remove_node(&(temp->right), p->data);
  }
  return temp;
}


void remove_node_iterative(BST *t, int d)
{
  if (!(*t))
  {
    printf("Tree not found!\n");
    return;
  }

  node *p, *q;
  p = *t;
  while (p)
  {
    if (p->data == d)
      break;

    q = p; // hold the address of p for backtracking
    if (p->data < d)
      p = p->right;
    else
      p = p->left;
  }

  if (!p)
    return;

  // CASE 1: deleting a leaf node (p : leaf node)
  if (!p->left && !p->right)
  {
    if (p == *t) // p is the root node
    {
      *t = NULL;
      free(p);
      return;
    }
    if (q->left == p)
      q->left = NULL;
    else if (q->right == p)
      q->right = NULL;
    free(p);
    return;
  }

  // CASE 2: node has left child only
  if (p->left && !p->right)
  {
    if (p == *t) // p is the root node
    {
      *t = p->left;
      free(p);
      return;
    }
    if (q->right == p)
      q->right = p->left;
    else
      q->left = p->left;

    free(p);
    return;
  }

  // CASE 3: node has right child only
  if (!p->left && p->right)
  {
    if (p == *t) // p is the root node
    {
      *t = p->right;
      free(p);
      return;
    }
    if (q->right == p)
      q->right = p->right;
    else
      q->left = p->right;

    free(p);
    return;
  }

  // CASE 4 : p has both left and right children
  node *k, *kp;
  kp = p->left;
  k = kp->right;

  while (k && k->right)
  {
    while (k->right)
    {
      kp = k;
      k = k->right;
    }
  }

  if (!k)
  {
    p->data = kp->data;
    p->left = kp->left;
    free(kp);
    return;
  }

  p->data = k->data;
  kp->right = NULL;
  free(k);

  return;
}


node *search(BST t, int d)
{
  node *temp = t;
  if (!t)
    return NULL;

  if (d == temp->data)
    return temp;

  else if (d > temp->data)
    search(temp->right, d);

  else if (d < temp->data)
    search(temp->left, d);
}


void inorder(BST t)
{
  if (!t)
    return;

  inorder(t->left);
  printf("%d ", t->data);
  inorder(t->right);
}


void preorder(BST t)
{
  if (!t)
    return;

  printf("%d ", t->data);
  preorder(t->left);
  preorder(t->right);
}


void postorder(BST t)
{
  if (!t)
    return;

  postorder(t->left);
  postorder(t->right);
  printf("%d ", t->data);
}


node *min_value_node(BST t)   
{
  node *curr = t;
  while (curr && curr->left != NULL)
  {
    curr = curr->left;
  }
  return curr;
}


int max_depth(BST t) // DFS
{
  if (!t)
    return -1;

  int ldepth = max_depth(t->left);
  int rdepth = max_depth(t->right);

  if (ldepth > rdepth)
    return ldepth + 1;
  else
    return rdepth + 1;

  return 0;
}


void display_level(BST t, int level)
{
  node *p, *q;
  p = t;
  q = NULL;
  if (level == 1)
  {
    printf("data : %d\n", t->data);
    return;
  }

  for (int i = 2; i <= level; i++)
  {
    q = p;
    if (p->left)
      p = p->left;
    else if (q->right)
      p = q->right;
    if (i == level)
      printf("data : %d\n", p->data);
  }

  if (q->right)
  {
    p = q->right;
    printf("data : %d\n", p->data);
  }

  return;
}
