typedef struct node{
    int value,row,col;
    struct node* right,*down;

}node;

typedef struct sparse{
    node **row,**col;
    int rw, cl;     //no. of rows and columns to make array of pointer to nodes
}sparse;

void init(sparse *,char*);

sparse* sparseadd(sparse* ,sparse* );

sparse* multimatrices(sparse* ,sparse* );

sparse *transpose(sparse *);

void printmat(sparse *);
