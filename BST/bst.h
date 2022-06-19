typedef struct node{
  struct node *left, *right;
  int data;
} node;

typedef node *BST;

void init_bst(BST *);
void insert_node(BST *, int);
node *remove_node(BST *, int );
void remove_node_iterative(BST *t, int d);
node *search(BST , int);

//traversals
void inorder(BST);
void postorder(BST);
void preorder(BST);
void display_level(BST, int);

int max_depth(BST);
