#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


int main(int argc, char *argv[])
{
  FILE *fptr;
  fptr = fopen(argv[1], "w");
  int size = atoi(argv[2]);

  for (int i = 0; i < size; i++)
  {
    fprintf(fptr, "%d\n", rand()/10000000);
  }

  fclose(fptr);

  FILE *fpr = fopen(argv[1], "r");
  int n;
  heap h;
  init_heap(&h, size);

  printf("Inserting elements into the heap...\n");
  while (fscanf(fpr, "%d", &n) != -1 )
  {
    printf("%d ",n);
    insert(&h, n);
  }

  printf("\n\nTraversing the heap\n");
  traverse(h);

  heap_sort(&h, size);
  return 0;
}



