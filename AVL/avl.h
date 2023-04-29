typedef struct node{
  int data, bf;
  struct node *left, *right, *parent;
} node;

typedef node *avl_node;


void init_avl(avl_node *);
void insert(avl_node *, int);
int height(avl_node);
void LL_rotation(avl_node *, avl_node *);
void RR_rotation(avl_node *, avl_node *);
void LR_rotation(avl_node *, avl_node *);
void RL_rotation(avl_node *, avl_node *);
avl_node imbalanced_node(avl_node);
void reassign_bf(avl_node);

void inorder(avl_node);
void preorder(avl_node);