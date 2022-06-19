typedef struct node{
    int* arr;
    int size, rear;
}* heap;

typedef struct node node;

void init_heap(heap* h, int sz);
void insert(heap* h, int d);
void remove_element(heap* h);
void level_order(heap h);
