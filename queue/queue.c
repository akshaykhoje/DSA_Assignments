#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"


void init_q(queue *q, int size)
{
  q->A = (int *)malloc(sizeof(int) * size);
  q->size = size;
  q->front = q->rear = -1;

  for (int i = 0; i < size; i++)
    q->A[i] = INT_MIN;
  
  return;
}


int is_q_full(queue q)
{
  if ((q.front == 0 && q.rear == q.size -1) || (q.front == q.rear+1))
    return 1;
  
  return 0;
}


int is_q_empty(queue q)
{
  if (q.front == -1)
    return 1;
  return 0;
}


void enqueue(queue *q, int n)
{
  if (is_q_full(*q))
    return;
  
  if (q->front == -1)
    q->front++;
  q->rear = (q->rear + 1) % q->size;
  q->A[q->rear] = n;

  return;
}


int dequeue(queue *q)
{
  int x = INT_MIN;
  if (is_q_empty(*q))
  {
    return x;
  }
  
  x = q->A[q->front];
  if (q->front == q->rear)
  {
    q->front = q->rear = -1;
    return x;
  }
  q->front = (q->front +1) % q->size;
  return x;
}


void display_queue(queue q)
{
  for (int i = 0; q.A[i] != INT_MIN; i++)
  {
    printf("%d ", q.A[i]); 
  }
  printf("\n");
  return;
}


void driver()
{
  queue q;
  int size;
  printf("Enter the size of the queue : ");
  scanf("%d", &size);
  init_q(&q, size);

  enqueue(&q, 6);
  enqueue(&q, 32);
  enqueue(&q, -9);
  enqueue(&q, 4);
  display_queue(q);
  printf("%d ",dequeue(&q));

  return;
}