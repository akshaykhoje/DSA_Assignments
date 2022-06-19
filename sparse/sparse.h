typedef struct node{
    int value,row,col;
    struct node* right,*down;

}node;

typedef struct sparse{
    node **row,**col;
    int rw, cl;
}sparse;

void init(sparse *,char*);

sparse* sparseadd(sparse* ,sparse* );

void multimatrices(sparse* ,sparse* );

void printmat(sparse *);
