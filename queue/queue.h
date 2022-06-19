typedef struct queue{
  int *A; //pointer to array containing queue elements
  int front, rear, size;
} queue;

void init_q(queue *, int);
int is_q_empty(queue );
int is_q_full(queue );
void enqueue(queue *, int);
int dequeue(queue *);
void display(queue);
void driver();

