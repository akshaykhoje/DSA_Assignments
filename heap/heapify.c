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

void swap(int* a, int* b){
    int tmp = *b;

    *b = *a;
    *a = tmp;

    return;
}

void heapify(heap* h){
    int i = (*h)->rear;

    int sw = 0;
    while(i >= 0){
        int pidx = (i - 1) / 2;

        sw = 0;
        if((*h)->arr[i] > (*h)->arr[pidx]){
            swap(&(*h)->arr[i] , &(*h)->arr[pidx]);
            sw = 1;
        }
        
        if(!sw) return;

        i = pidx;
    }

    return;
}

void heapify_top(heap* h){
    int i = 0;

    while(i <= (*h)->rear){
        int id1 = 2*i + 1;
        int id2 = 2*i + 2;

        int sw = 0;
        if(id1 > (*h)->rear || id2 > (*h)->rear) return;

        if(((*h)->arr[id1] > (*h)->arr[i]) &&  ((*h)->arr[id2] > (*h)->arr[i])){
            if((*h)->arr[id1] > (*h)->arr[id2]){
                swap(&(*h)->arr[i], &(*h)->arr[id1]);
                i = id1;
            }
            else{
                swap(&(*h)->arr[i], &(*h)->arr[id2]);
                i = id2;
            }
            sw = 1;
        }
        else if((*h)->arr[id1] > (*h)->arr[i]){
            swap(&(*h)->arr[i], &(*h)->arr[id1]);
            i = id1;
            sw = 1;
        }
        else if((*h)->arr[id2] > (*h)->arr[i]){
            swap(&(*h)->arr[i], &(*h)->arr[id2]);
            i = id2;
            sw = 1;
        }


        if(!sw) return;
    }

    return;
}

void sorted_result(heap h){
    int i=0; 

    while(h->arr[i] != INT_MIN){
        printf("%d ", h->arr[i++]);
    }
}