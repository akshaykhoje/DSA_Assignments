#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef HEAP
#define HEAP
#include "heap.h"
#endif

#ifndef HEAPIFY
#define HEAPIFY
#include "heapify.h"
#endif

void init_heap(heap* h, int sz){
    *h = (node*)malloc(sizeof(node));
    (*h)->arr = (int*)malloc(sz*sizeof(int));
    (*h)->size = sz;
    (*h)->rear = -1;

    for(int i=0; i<sz; i++)
        (*h)->arr[i] = INT_MIN;

    return;
}

void insert(heap* h, int d){
    (*h)->arr[++(*h)->rear] = d;

    int pidx = ((*h)->rear - 1) / 2;
    int idx = (*h)->rear;

    if((*h)->arr[idx] > (*h)->arr[pidx])
        heapify(h);

    return;
}

void remove_element(heap* h){
    if((*h)->rear == -1) return;
    
    swap(&(*h)->arr[(*h)->rear], &(*h)->arr[0]);

    (*h)->rear--;
    heapify_top(h);
}

void level_order(heap h){
    for(int i=0; i<h->size; i++)
        printf("%d ", h->arr[i]);
    printf("\n");

    return;
}
