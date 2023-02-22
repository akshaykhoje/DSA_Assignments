#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "heapify.h"



int main(int argc, char* argv[]){
    heap h;
    int tot_num = 0;
    int* arr = malloc(10*sizeof(int));

    FILE* fp = fopen(argv[1], "r");

    if(!fp){
        printf("Error opening the file\n");
        return 0;
    }

    int num = 0, j = 0;
    char ch;
    int prev_size = 10;
    while(!feof(fp)){
        ch = fgetc(fp);

        if(ch >= '0' && ch <= '9'){
            num = num*10 + (ch - '0');
        }
        else if(ch == '\n'){
            num = 0;
            continue;
        }
        else{
            if(j >= prev_size){
                int sz = sizeof(arr) / sizeof(arr[0]);

                int* tmp = realloc(arr, (prev_size + 10)*sizeof(int));
                prev_size += 10;
                if(!tmp){
                    printf("Heap Overflow\n");
                    return 0;
                }
                arr = tmp;
            }
            arr[j++] = num;
            num = 0;
        }
    }
    fclose(fp);

    init_heap(&h, prev_size);

    for(int i=0; i<j; i++)
        insert(&h, arr[i]);
    

    for(int i=0; i<j-1; i++)
        remove_element(&h);
    
    fp = fopen("result.txt", "w");

    if(!fp){
        printf("result.txt file opening error\n");
        return 0;
    }

    int cnt = 0;
    int i = 0;
    while(h->arr[i] != INT_MIN){
        fprintf(fp, "%d ", h->arr[i++]);
        if(cnt == 20){
            fprintf(fp, "\n");
            cnt = 0;
        }
        cnt++;
    }

    printf("Sorted result stored in result.txt\n");

    fclose(fp);
    return 0;
}