#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int row;
    int column;
    int data;
    struct node *right;
    struct node *down;
} node;

typedef struct sparse
{
    node **top;
    node **side;
    int size;
} sparse;

void insert(sparse *s, node *nn)
{

    if (s->side[nn->row] == NULL)
    {
        s->side[nn->row] = nn;
    }
    else
    {
        node *side = s->side[nn->row];
        while (side->right != NULL)
        {
            side = side->right;
        }
        side->right = nn;
    }

    if (s->top[nn->column] == NULL)
    {
        s->top[nn->column] = nn;
    }
    else
    {
        node *top = s->top[nn->column];
        while (top->down != NULL)
        {
            top = top->down;
        }
        top->down = nn;
    }
}

void make_node_n_insert(sparse *s, int row, int column, int data)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->row = row;
    nn->column = column;
    nn->data = data;
    nn->right = NULL;
    nn->down = NULL;
    insert(s, nn);
}

void make_sparse(sparse *s, char *filename)
{
    FILE *f = fopen(filename, "r");
    fscanf(f, "%d", &s->size);

    s->top = (node **)malloc(sizeof(node *) * s->size);
    s->side = (node **)malloc(sizeof(node *) * s->size);

    for (int i = 0; i < s->size; i++)
    {
        s->top[i] = NULL;
        s->side[i] = NULL;
    }
    int n;
    for (int i = 0; i < s->size; i++)
    {
        for (int j = 0; j < s->size; j++)
        {
            fscanf(f, "%d", &n);
            if (n != 0)
            {
                make_node_n_insert(s, i, j, n);
            }
        }
    }
}

void print_sparse(sparse s)
{
    node *ptr;
    for (int i = 0; i < s.size; i++)
    {
        ptr = s.side[i];
        while (ptr != NULL)
        {
            printf("Row: %d Column: %d Weight: %d\n", ptr->row, ptr->column, ptr->data);
            ptr = ptr->right;
        }
    }
}

sparse add(sparse s1, sparse s2)
{
    sparse s;
    s.side = (node **)malloc(sizeof(node) * s1.size);
    s.top = (node **)malloc(sizeof(node) * s1.size);
    s.size = s1.size;
    for (int i = 0; i < s.size; i++)
    {
        s.top[i] = NULL;
        s.side[i] = NULL;
    }

    node *ptr;
    node *ptr1;
    node *ptr2;
    for (int i = 0; i < s.size; i++)
    {
        ptr = s.side[i];
        ptr1 = s1.side[i];
        ptr2 = s2.side[i];
        while (ptr1 != NULL && ptr2 != NULL)
        {
            if (ptr1->column == ptr2->column)
            {
                int sum = ptr1->data + ptr2->data;
                if (sum > 0)
                {
                    make_node_n_insert(&s, ptr1->row, ptr1->column, sum);
                }
                ptr1 = ptr1->right;
                ptr2 = ptr2->right;
            }
            else if (ptr1->column < ptr2->column)
            {
                make_node_n_insert(&s, ptr1->row, ptr1->column, ptr1->data);
                ptr1 = ptr1->right;
            }
            else if (ptr2->column < ptr1->column)
            {
                make_node_n_insert(&s, ptr2->row, ptr2->column, ptr2->data);
                ptr2 = ptr2->right;
            }
        }
        while (ptr1 != NULL)
        {
            make_node_n_insert(&s, ptr1->row, ptr1->column, ptr1->data);
            ptr1 = ptr1->right;
        }
        while (ptr2 != NULL)
        {
            make_node_n_insert(&s, ptr2->row, ptr2->column, ptr2->data);
            ptr2 = ptr2->right;
        }
    }
    return s;
}

int main()
{
    sparse s1;
    sparse s2;
    make_sparse(&s1, "sample.txt");
    make_sparse(&s2, "sparse.txt");
    // print_sparse(s1);
    // print_sparse(s2);
    sparse s = add(s1, s2);
    print_sparse(s);
}

