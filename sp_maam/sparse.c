#include "sparse.h"
#include <stdlib.h>
#include <stdio.h>

void init_matrix(sparse *s, char *filename)
{
  FILE *fp = fopen(filename, "r");
  int r, c;

  fscanf(fp, "%d\n", &r);
  s->r = r;
  fscanf(fp, "%d\n", &c);
  s->c = c;

  s->row = (node *)malloc(sizeof(node) * r);
  s->col = (node *)malloc(sizeof(node) * c);

  for (int i = 0; i < r; i++)
  {
    s->row[i] = NULL;
  }

  for (int i = 0; i < c; i++)
  {
    s->col[i] = NULL;
  }
  int value;
  node *nn;
  // node *tr, *tc;
  for (int i = 0; i < r; i++)
  {

    for (int j = 0; j < c; j++)
    {

      fscanf(fp, "%d ", &value);

      if (value != 0)
      {
        nn = (node *)malloc(sizeof(node));
        nn->down = NULL;
        nn->right = NULL;
        nn->data = value;
        nn->i = i;
        nn->j = j;
        insertnode(s, nn, i, j);
      }
      // printf( "%d, %d, %d\n", i,j,value);
    }
  }
  fclose(fp);
  return;
}

void insertnode(sparse *s, node *nn, int i, int j)
{
  node *tr, *tc;
  if (s->row[i] == NULL)
  {
    s->row[i] = nn;
  }
  else
  {
    tr = s->row[i];
    while (tr->right != NULL)
      tr = tr->right;
    tr->right = nn;
  }

  if (s->col[j] == NULL)
  {
    s->col[j] = nn;
  }
  else
  {
    tc = s->col[j];
    while (tc->down != NULL)
      tc = tc->down;
    tc->down = nn;
  }
  return;
}

void display(sparse g)
{
  node *p;
  node *q;
  printf("\nRow - column - data : \n");
  for (int i = 0; i < g.r; i++)
  {
    p = g.row[i];
    if (p)
    {
      for (int j = 0; j < g.c; j++)
      {
        q = g.col[j];
        while (q)
        {
          if (p == q)
          {
            printf("%d - %d - %d\n", p->i, p->j, p->data);
            p = p->right;
            break;
          }
          q = q->down;
        }
      }
    }
  }
  return;
}

sparse addSparse(sparse s1, sparse s2)
{
  sparse s3;

  if (s1.r != s2.r || s1.c != s2.c)
  {
    printf("Incompatible matrices\n");
    return s3;
  }

  s3.r = s1.r;
  s3.c = s1.c;

  s3.row = (node *)malloc(sizeof(node) * s3.r);
  s3.col = (node *)malloc(sizeof(node) * s3.c);

  for (int i = 0; i < s3.r; i++)
  {
    s3.row[i] = NULL;
  }

  for (int i = 0; i < s3.c; i++)
  {
    s3.col[i] = NULL;
  }

  // display(s3);
  node *p, *q, *nn;

  int i;
  // node *tr, *tc;
  for (i = 0; i < s1.r; i++)
  {
    p = s1.row[i];
    q = s2.row[i];
    while (p && q)
    {
      nn = (node *)malloc(sizeof(node));
      nn->down = NULL;
      nn->right = NULL;
      nn->i = i;
      // check for i and j equality
      if (p->j == q->j)
      {
        // insert a node with i,j,p->val + q->val
        nn->j = p->j;
        nn->data = p->data + q->data;
        p = p->right;
        q = q->right;
      }
      else if (p->j < q->j)
      {
        // insert p node
        nn->data = p->data;
        nn->j = p->j;
        p = p->right;
      }
      else
      {
        // insert q
        nn->data = q->data;
        nn->j = q->j;
        q = q->right;
      }
      insertnode(&s3, nn, nn->i, nn->j);
    }

    while (p)
    {
      nn = (node *)malloc(sizeof(node));
      nn->down = NULL;
      nn->right = NULL;
      nn->i = p->i;
      nn->j = p->j;
      nn->data = p->data;
      insertnode(&s3, nn, nn->i, nn->j);
      p = p->right;
    }
    while (q)
    {
      nn = (node *)malloc(sizeof(node));
      nn->down = NULL;
      nn->right = NULL;
      nn->i = q->i;
      nn->j = q->j;
      nn->data = q->data;
      insertnode(&s3, nn, nn->i, nn->j);
      q = q->right;
    }
  }
  // display(s3);
  return (s3);
}