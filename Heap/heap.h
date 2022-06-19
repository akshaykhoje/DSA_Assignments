typedef struct {
  int *A, rear, size;
} heap;

void init_heap(heap *, int);
void insert(heap *, int);
void traverse(heap );
int Remove(heap *);
void Remove_heapify(heap *, int);
void heapify(heap *, int);
int get_max(heap);
void heap_sort(heap *, int );



