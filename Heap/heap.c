#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "heap.h"


void init_heap(heap *h, int s)
{
  h->size = s;
  h->A = (int *)malloc(sizeof(int) * s);
  h->rear = -1;

  for (int i = 0; i < h->size; i++)
    h->A[i] = INT_MIN;

  return;
}


void insert(heap *h, int key)
{
  if (h->rear == h->size - 1)         // heap is full
  {
    return;
  }

  h->A[++(h->rear)] = key;

  // check if it is a heap
  int rear_parent = (h->rear - 1) / 2;
  if (h->A[h->rear] > h->A[rear_parent])
    heapify(h, h->rear);

  return;
}


void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;

  return;
}


void heapify(heap *h, int rear)
{
  int pi = (rear - 1) / 2;    // parent index

  if (rear > 0 && h->A[rear] > h->A[pi])
  {
    swap(&(h->A[rear]), &(h->A[pi]));
    heapify(h, pi);
  }

  return;
}


void traverse(heap h)
{
  int k = 0;
  for (int i = 0; i <= h.rear; i++)
  {
    printf("%d\t", h.A[i]);
  }
  printf("\n");
  return;
}


int Remove(heap *h)
{
  if (h->rear == -1)       // heap is empty
  {
    return 0;
  }
  int x = h->A[0];
  swap(&(h->A[0]), &(h->A[h->rear]));
  h->rear--;
  Remove_heapify(h, 0);
  return x;
}


void Remove_heapify(heap *h, int i)
{
  int largest = i;
  int left_child = 2 * largest + 1;
  int right_child = 2 * largest + 2;

  // if left child is larger than the right child
  if (left_child < h->rear && h->A[left_child] > h->A[largest])
  {
    largest = left_child;
  }
  // if right child is larger than the left child
  if (right_child < h->rear && h->A[right_child] > h->A[largest])
  {
    largest = right_child;
  }
  // if largest is not root
  if (largest != i)
  {
    swap(&(h->A[i]), &(h->A[largest]));
    Remove_heapify(h, largest);
  }

  return;
}


int get_max(heap h)
{
  if (h.rear == -1)
    return INT_MIN;

  return h.A[0];
}


void heap_sort(heap *h, int s)
{
  heap h1;
  init_heap(&h1, s);

  int *arr = h->A;

  for (int i = 0; i < s; i++)
    insert(&h1, arr[i]);

  for (int i = s-1; i >= 0; i--)
    arr[i] = Remove(&h1);

  FILE *fp;
  fp = fopen("sorted.txt", "w");
  printf("\n\nSorted heap data is stored in sorted.txt \n\n");
  for (int i = 0; i < s; i++)
  {
    if (arr[i] == INT_MIN)
      continue;
    fprintf(fp, "%d\n", arr[i]);
  }
  
  return;
}








